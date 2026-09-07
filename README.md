# My robocup

An STM32F407VETx-based smart car control project featuring vehicle control, encoder feedback and PWM, LiDAR data processing, ESP-01S/W5500 network communication, and a Python tool for receiving and visualizing point cloud data.

nhyo：唉，也是希望有人能发扬光大吧（悲
## 主要内容

- STM32F407VETx 固件工程（Keil MDK-ARM）
- 电机 PWM 与编码器读取
- 激光雷达数据读取与图像/控制处理
- ESP-01S Wi-Fi UDP 通信
- W5500 以太网 UDP 通信
- Python 点云接收与可视化工具 `n10p.py`

## 目录结构

```text
.
├─ Core/                         STM32CubeMX 生成的核心代码
├─ Drivers/                      构建所需的 HAL 与 CMSIS 文件
├─ MDK-ARM/
│  ├─ Library/                   项目功能代码
│  ├─ RTE/                       Keil RTE 配置
│  ├─ RACE.uvprojx               Keil 工程文件
│  └─ startup_stm32f407xx.s      启动文件
├─ RACE.ioc                      STM32CubeMX 工程配置
├─ n10p.py                       UDP 点云接收与显示工具
└─ requirements.txt              Python 依赖
```

## 使用方法

### 固件

1. 使用 Keil MDK-ARM 打开 `MDK-ARM/RACE.uvprojx`。
2. 确认已安装工程所需的 STM32F4 Device Family Pack。
3. 在 `MDK-ARM/Library/Inc/vofa.h` 中修改 Wi-Fi 名称、密码和接收端 IP。
4. 根据实际网络修改 `MDK-ARM/Library/Src/w5500.c` 中的 W5500 MAC、IP、网关和目标地址。
5. 编译并下载到 STM32F407VETx 目标板。


### Python 点云工具

```shell
python -m pip install -r requirements.txt
python n10p.py
```

`n10p.py` 默认监听 `0.0.0.0:8082`。运行前请确认防火墙允许本机接收相应 UDP 数据。


## 发布与许可说明

- 编译产物、调试输出、IDE 个人状态、抓取数据、压缩包和临时文件已通过 `.gitignore` 排除。
- 仓库内保留了构建所需的 STM32 HAL/CMSIS 文件及其原许可证，详见 `THIRD_PARTY_NOTICES.md`。
- 当前没有为项目自有代码添加开源许可证。在获得相关作者明确授权前，不应自行声明 MIT、GPL、Apache-2.0 等许可证。


## 作者联系

TangSong404 和 MindFreak(hzr)，请通过 GitHub 联系本仓库所有者。
