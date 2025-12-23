#include "fancontrol.h"

// 内部堆大小，按需调整, 50KB.
#define INNER_HEAP_SIZE 0xC800

#ifdef __cplusplus
extern "C" {
#endif

// Sysmodules 不应该使用 Applet.
u32 __nx_applet_type = AppletType_None;

// Sysmodules 通常只需要使用一个 FS 会话.
u32 __nx_fs_num_sessions = 1;

// Newlib 堆配置函数 (使 malloc/free 工作).
void __libnx_initheap(void)
{
    static u8 inner_heap[INNER_HEAP_SIZE];
    extern void* fake_heap_start;
    extern void* fake_heap_end;

    // 配置 Newlib 堆.
    fake_heap_start = inner_heap;
    fake_heap_end   = inner_heap + sizeof(inner_heap);
}

// 初始化.
void __appInit(void)
{
    Result rc;

    rc = smInitialize();
    if (R_FAILED(rc))
        diagAbortWithResult(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    rc = setsysInitialize();
    if (R_SUCCEEDED(rc)) {
        SetSysFirmwareVersion fw;
        rc = setsysGetFirmwareVersion(&fw);
        if (R_SUCCEEDED(rc))
            hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
        setsysExit();
    }

    rc = fsInitialize();
    if (R_FAILED(rc))
        diagAbortWithResult(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));       

    rc = fsdevMountSdmc();;
    if (R_FAILED(rc))
        diagAbortWithResult(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    rc = fanInitialize();
    if (R_FAILED(rc))
        diagAbortWithResult(MAKERESULT(Module_Libnx, LibnxError_ShouldNotHappen));

    rc = i2cInitialize();
    if (R_FAILED(rc))
        diagAbortWithResult(MAKERESULT(Module_Libnx, LibnxError_ShouldNotHappen));

    smExit();
}

// 安全退出.
void __appExit(void)
{
    CloseFanControllerThread();
    fanExit();
    i2cExit();
    fsExit();
    fsdevUnmountAll();
}

#ifdef __cplusplus
}
#endif

// 主入口点.
int main(int argc, char* argv[])
{
    TemperaturePoint *table;
    
    ReadConfigFile(&table);
    InitFanController(table);
    StartFanControllerThread();
    WaitFanController();

    return 0;
}
