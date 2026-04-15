# Lab 1b — ISR Entry Latency
Date: YYYY-MM-DD
Board: NUCLEO-F446RE
Clock: 180 MHz
Measurement tool: DWT->CYCCNT

## Hypothesis
Minimum: 12 cycles = 67ns — ARM architectural minimum for Cortex-M4.
Maximum: 14-16 cycles = 78-89ns — variation from instruction boundary timing.
Range: 2-4 cycles — jitter from interrupt arrival moment.

## Setup
- PA5: ISR entry probe — first instruction of TIM2_IRQHandler sets PA5 high
- PA6: main loop probe — continuous toggle in tight infinite loop
- TIM2: 1kHz update interrupt (PSC=89, ARR=999, TIM2 clock=90MHz)
- Measurement: DWT->CYCCNT snapshot in main loop + first line of ISR
- 100 capture events recorded
- ART enabled throughout

## Results

| Metric       | Cycles | ns   | Notes                              |
|--------------|--------|------|------------------------------------|
| Minimum      |        |      | best case — clean instruction boundary |
| Maximum      |        |      | worst case — multi-cycle instruction   |
| Range        |        |      | jitter = max - min                     |
| Mean (approx)|        |      | eyeball average                        |

Capture count: 100

ARM architectural minimum (Cortex-M4): 12 cycles = 67ns
Your measured minimum vs architectural spec: delta = X cycles

## Raw DWT readings (first 10 captures)
| Capture | latency_cycles | latency_ns |
|---------|---------------|------------|
| 1       |               |            |
| 2       |               |            |
| 3       |               |            |
| 4       |               |            |
| 5       |               |            |
| 6       |               |            |
| 7       |               |            |
| 8       |               |            |
| 9       |               |            |
| 10      |               |            |

## What Surprised Me
[mandatory — minimum one paragraph]
[example topics: did the minimum match the 12-cycle spec?
 how much variation did you see across 100 captures?
 what instruction do you think was running at worst-case captures?
 how does 67ns compare to what you expected interrupt latency to be?
 what does the range tell you about scheduling precision?]