# NX-FanControl

**NX-FanControl** is a Nintendo Switch homebrew utility that lets you fully customize your console’s internal fan curve.
It supports up to **10 configurable points** based on SoC temperature, giving you full control over cooling performance and noise levels.

---

## ✨ Features

* 🧠 **Custom fan curve** — Define up to **10 temperature points** with corresponding fan speeds.
* 🌡️ **Real-time monitoring** — View the current **SoC temperature** and **fan RPM** in real time.
* ⚙️ **Fine-tuned control** — Balance cooling, noise, and performance exactly to your preference.

---

## 📦 Requirements

Before building, ensure you have the [**devkitPro toolchain**](https://devkitpro.org/wiki/Getting_Started) installed and properly set up.

---

## 🛠️ Building from Source

Clone the repository (including submodules), install dependencies, and build:

```bash
git clone --recurse-submodules https://github.com/nangongjing1/NX-FanControl_Mod.git
cd NX-FanControl_Mod
make
```

---

## ⚙️ Common Issues & Fixes

**Issue:** Fan always stays on
**Fix:** Add the following configuration to your Atmosphère setup:
[👉 system_settings.ini (GitHub link)](https://github.com/dominatorul/Easy-Setup/blob/main/data/Optimizer/EmuNAND/system_settings.ini)

Place it in:

```
atmosphere/config/
```

---

## ⚠️ Disclaimer

This project is **homebrew software** and is **not affiliated with or endorsed by Nintendo**.
Use at your own risk — modifying fan behavior may affect system stability, performance, or hardware lifespan.

---

## 📜 License

This project is licensed under the **MIT License**.
See the [LICENSE](./LICENSE) file for details.

The [libultrahand](https://github.com/ppkantorski/libultrahand) is licensed and distributed under [GPLv2](https://github.com/ppkantorski/libultrahand/blob/main/LICENSE) with a [custom library](./overlay/lib/libultrahand/libultra) utilizing [CC-BY-4.0](https://github.com/ppkantorski/libultrahand/blob/main/SUB_LICENSE).
