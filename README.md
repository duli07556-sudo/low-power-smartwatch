# STM32 Embedded Projects

这个仓库用于管理两个 STM32 嵌入式工程的源代码，并通过 Git 提交记录保存 IAP 工程从原版到改进版的变化。

## 工程目录

| 目录 | 说明 |
| --- | --- |
| `IAP_F411` | STM32F411 IAP 原版工程，使用 YMODEM 通过串口更新固件 |
| `OV_Watch` | 基于 STM32F411、FreeRTOS 和 LVGL 的手表工程 |

## 开发环境

- STM32CubeMX：使用 `.ioc` 文件查看和调整芯片配置
- Keil MDK-ARM：使用 `.uvprojx` 文件打开工程

## Git 版本

- `iap-v1.0-original`：IAP 原版，同时加入 OV Watch 工程

编译生成的目标文件、链接文件和日志没有纳入版本管理，可在本地重新编译生成。
