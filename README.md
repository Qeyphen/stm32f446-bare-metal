# STM32F446 Bare Metal

Bare metal firmware for the STM32F446RE written from scratch — no HAL, no CubeMX, no abstraction layers. Direct register access only.

## What this is

A learning project building up from zero: custom startup file, linker script, minimal register definitions, and a from-scratch clock configuration that takes the chip from 16MHz HSI to 180MHz via the main PLL.

Built as part of a low-level systems and embedded engineering curriculum covering clock configuration, pipeline timing, and interrupt latency on Cortex-M4.

## Hardware

- Board: STM32F446RE Nucleo
- Core: ARM Cortex-M4 at 180MHz
- Flash: 512KB — RAM: 128KB

## Project structure