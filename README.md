# STM32 Embedded Projects

这个仓库用于管理两个 STM32 嵌入式工程的源代码，并通过 Git 提交记录保存 IAP 工程从原版到改进版的变化。

## 工程目录

| 目录 | 说明 |
| --- | --- |
| `IAP_F411改进` | STM32F411 IAP 改进版工程，使用 YMODEM 通过串口更新固件 |
| `OV_Watch` | 基于 STM32F411、FreeRTOS 和 LVGL 的手表工程 |

## IAP 改进内容

- 接收 YMODEM 数据包时校验 CRC16，错误数据包不会写入 Flash
- 按照 YMODEM 流程完成双 EOT 结束握手
- 擦除 APP Flag 扇区失败时终止升级并输出错误信息
- 手动跳转到应用程序前检查 APP Flag，避免跳转到无效程序
- 固件下载结束后延时输出状态信息，减少与上位机串口占用的冲突

## 开发环境

- STM32CubeMX：使用 `.ioc` 文件查看和调整芯片配置
- Keil MDK-ARM：使用 `.uvprojx` 文件打开工程

## Git 版本

- [`iap-v1.0-original`](https://github.com/duli07556-sudo/stm32-embedded-projects/tree/iap-v1.0-original)：IAP 原版，同时加入 OV Watch 工程
- [`iap-v2.0-improved`](https://github.com/duli07556-sudo/stm32-embedded-projects/tree/iap-v2.0-improved)：IAP 改进版
- [查看原版与改进版的提交差异](https://github.com/duli07556-sudo/stm32-embedded-projects/compare/iap-v1.0-original...iap-v2.0-improved)

编译生成的目标文件、链接文件和日志没有纳入版本管理，可在本地重新编译生成。
