// main.cpp
// 在包含 tesla.hpp 前定义 TESLA_INIT_IMPL
#define TESLA_INIT_IMPL
#include <tesla.hpp>
#include "main_menu.hpp"

class NxFanControlOverlay : public tsl::Overlay {
public:
    virtual void initServices() override {
        // Tesla 自动处理所有的显示/分辨率设置
        // 这里只初始化你的服务
        fsdevMountSdmc();
        pmshellInitialize();
    }
    
    virtual void exitServices() override {
        fsdevUnmountAll();
        pmshellExit();
    }

    virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        return initially<MainMenu>();
    }
};

int main(int argc, char **argv) {
    // Tesla 处理所有的初始化，键组合检测，分辨率等.
    // 你的 .ovl 只提供GUI
    return tsl::loop<NxFanControlOverlay>(argc, argv);
}