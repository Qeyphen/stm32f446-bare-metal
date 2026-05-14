# Lab 1b — ISR Entry Latency
Date: 2026-05-13
Board: NUCLEO-F446RE
Clock: 180 MHz
Optimization: -O2, ART on
Measurement: DWT->CYCCNT

## Hypothesis
Minimum: 12 cycles = 67ns — ARM Cortex-M4 architectural minimum.
Maximum: 14-16 cycles = 78-89ns — variation from instruction boundary timing.
Range: 2-4 cycles — jitter from when interrupt arrives in the loop.

## Setup
- PA5 — set high as first instruction of TIM2_IRQHandler (ISR entry marker)
- PA6 — toggled continuously in main loop (preemption reference)
- TIM2 — 1kHz update interrupt, PSC=89, ARR=999, TIM2 clock=90MHz
- DWT->CYCCNT snapshot taken at end of main loop and first line of ISR
- DWT overhead calibrated (5 cycles) and subtracted from each measurement
- 100 captures, ART on, -O2

## Results

| Metric       | Cycles | ns     | Notes                          |
|--------------|--------|--------|--------------------------------|
| Minimum      | 19     | 105.6  | after 5-cycle overhead removed |
| Maximum      | 184    | 1022.2 | race condition artifact        |
| Range        | 165    | 916.7  | caused by race condition       |
| DWT overhead | 5      | 27.8   | measured, subtracted           |

Captures: 100 — consistent across 5 independent runs.

ARM spec minimum: 12 cycles = 67ns
Measured minimum: 19 cycles = 105.6ns
Delta: 7 cycles — instruction boundary overhead, cannot be removed in software

Breakdown of measured minimum:
  12 cycles  hardware stacking
   + additional software-visible timing effects
  19 cycles  measured

## Note on Maximum
184 cycles is a measurement artifact. It happens when TIM2 fires just
before last_main_cycle is updated — the subtraction uses a stale value
from the previous iteration. The observed 184-cycle values are measurement 
artifacts and do not represent true interrupt-entry latency.
The race cannot be fully eliminated in software without disabling interrupts
around the measurement point.

## Raw DWT Readings
Individual captures not recorded — only min/max tracked across 100 captures.
Results were identical across 5 independent runs confirming repeatability.

## What Surprised Me
Although the Cortex-M4 has a 12-cycle interrupt entry latency under 
ideal conditions, I measured 19 cycles minimum after subtracting the 
5-cycle DWT read overhead — still 7 cycles above the ARM specification. 
This confirmed that the 12-cycle figure is an architectural floor, not 
something a software measurement can reach directly. The gap comes from 
the instructions that execute between writing last_main_cycle and the 
interrupt actually firing, plus pipeline delays inside the ISR. Even 
replacing DWT with a logic analyzer would not close this gap entirely — 
PA5 is set by the first ISR instruction, not by the hardware stacking 
completing, so any pin-based measurement still includes instruction 
boundary overhead on top of the 12-cycle architectural constant.