#include "main.h"
#include "system_clock.h"

static void test1_mco2_output(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~(3UL << 18);
    GPIOC->MODER |=  (2UL << 18);

    GPIOC->AFR[1] &= ~(0xFUL << 4);
    GPIOC->AFR[1] |=  (0x0UL << 4);

    RCC->CFGR &= ~(7UL << 27);
    RCC->CFGR |=  (4UL << 27);

    while(1) {}
}

static void test2_systick_blink(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(3UL << 10);
    GPIOA->MODER |=  (1UL << 10);

    SysTick->LOAD = 179999;
    SysTick->VAL  = 0;
    SysTick->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSOURCE;

    uint32_t ms_count = 0;

    while(1)
    {
        if (SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG)
        {
            ms_count++;
            if (ms_count >= 1000)
            {
                ms_count = 0;
                if (GPIOA->ODR & (1UL << 5))
                    GPIOA->BSRR = GPIO_BSRR_BR5;
                else
                    GPIOA->BSRR = GPIO_BSRR_BS5;
            }
        }
    }
}

int main(void)
{
    SystemClock_Config();

    // test2_systick_blink();
    test1_mco2_output();
}