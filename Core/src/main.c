#include "main.h"
#include "system_clock.h"
#include "dwt.h"

volatile uint32_t cycles_per_1000ms = 0;
volatile uint32_t measured_mhz      = 0;

int main(void)
{
    SystemClock_Config();
    DWT_Init();

    SysTick->LOAD = 179999;
    SysTick->VAL  = 0;
    SysTick->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSOURCE;

    while (!(SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG));

    uint32_t start = DWT_GetCycles();

    uint32_t tick_count = 0;
    while (tick_count < 1000)
    {
        if (SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG)
        {
            tick_count++;
        }
    }

    cycles_per_1000ms = DWT_ElapsedCycles(start);

    measured_mhz = cycles_per_1000ms / 1000000;

    // expected results
    // cycles_per_1000ms ≈ 180,000,000
    // measured_mhz      ≈ 180
    //
    // if measured_mhz ≈ 16  -> still on HSI, PLL never switched
    // if measured_mhz ≈ 8   -> stuck on HSE
    // if measured_mhz ≈ 90  -> PLLP wrong, dividing by 4 not 2
    // if measured_mhz ≈ 180 -> correct ✓

    while(1) {}
}