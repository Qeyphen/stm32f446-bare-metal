#include "system_clock.h"

void SystemClock_Config(void) {
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    (void)RCC->APB1ENR;
    PWR->CR |= PWR_CR_VOS;

    // Configure flash latency
    #ifdef DISABLE_ART
        FLASH->ACR = FLASH_ACR_LATENCY_5WS;
    #else
        FLASH->ACR = FLASH_ACR_LATENCY_5WS |
                     FLASH_ACR_PRFTEN      |
                     FLASH_ACR_ICEN        |
                     FLASH_ACR_DCEN;
    #endif

    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_PPRE1_Msk | RCC_CFGR_PPRE2_Msk);
    RCC->CFGR |=  (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2);

    // Configure PLL: 8MHz HSE / 4 * 180 / 2 = 180MHz
    RCC->PLLCFGR = (4  << RCC_PLLCFGR_PLLM_Pos) |
                   (180 << RCC_PLLCFGR_PLLN_Pos) |
                   (0   << RCC_PLLCFGR_PLLP_Pos) |
                   RCC_PLLCFGR_PLLSRC_HSE         |
                   (8   << RCC_PLLCFGR_PLLQ_Pos);

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);
}