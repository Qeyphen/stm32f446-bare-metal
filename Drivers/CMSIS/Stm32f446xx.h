#ifndef STM32F446XX_H
#define STM32F446XX_H

#include <stdint.h>

#define __IO volatile
#define __I volatile const
#define __O volatile

// The register layouts and associated definitions are derived from the
// STM32F446xx Reference Manual (RM0390):
// https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx.pdf

// RCC
#define RCC_BASE 0x40023800UL
typedef struct {
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t RESERVED0;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
  uint32_t RESERVED1;
  uint32_t RESERVED2;
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t RESERVED3;
  __IO uint32_t APB1ENR;
  __IO uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

#define RCC_CR_HSEON (1UL << 16)
#define RCC_CR_HSERDY (1UL << 17)
#define RCC_CR_PLLON (1UL << 24)
#define RCC_CR_PLLRDY (1UL << 25)

#define RCC_APB1ENR_PWREN (1UL << 28)
#define RCC_AHB1ENR_GPIOAEN (1UL << 0)

#define RCC_CFGR_HPRE_DIV1 (0UL << 4)
#define RCC_CFGR_PPRE1_DIV4 (5UL << 10)
#define RCC_CFGR_PPRE2_DIV2 (4UL << 13)
#define RCC_CFGR_SWS_PLL (2UL << 2)
#define RCC_CFGR_SW_PLL (2UL << 0)
#define RCC_CFGR_SWS_Msk (3UL << 2) // mask for SWS field

#define RCC_CFGR_HPRE_Msk    (0xFUL  << 4U)
#define RCC_CFGR_PPRE1_Msk   (0x7UL  << 10U)
#define RCC_CFGR_PPRE2_Msk   (0x7UL  << 13U)

#define RCC_PLLCFGR_PLLM_Pos 0U
#define RCC_PLLCFGR_PLLN_Pos 6U
#define RCC_PLLCFGR_PLLP_Pos 16U
#define RCC_PLLCFGR_PLLQ_Pos 24U
#define RCC_PLLCFGR_PLLSRC_HSE (1UL << 22) // HSE as PLL source

// PWR
#define PWR_BASE 0x40007000UL
typedef struct {
  __IO uint32_t CR;
  __IO uint32_t ACR;
} PWR_TypeDef;

#define PWR ((PWR_TypeDef *)PWR_BASE)

#define PWR_CR_VOS (3 << 14)

// FLASH
#define FLASH_BASE 0x40023C00UL
typedef struct {
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t OPTCR;
} FLASH_TypeDef;

#define FLASH ((FLASH_TypeDef *)FLASH_BASE)

#define FLASH_ACR_LATENCY (5 << 0)
#define FLASH_ACR_PRFTEN (1UL << 8)
#define FLASH_ACR_ICEN (1UL << 9)
#define FLASH_ACR_DCEN (1UL << 10)
#define FLASH_ACR_LATENCY_5WS (5UL << 0) // 5 wait states for 180 MHz

#define GPIOA_BASE 0x40020000UL

typedef struct {
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __I uint32_t IDR;
  __IO uint32_t ODR;
  __O uint32_t BSRR;
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

#define GPIO_MODER_MODE_OUTPUT(pin)   (1UL << ((pin) * 2))
#define GPIO_MODER_CLEAR(pin)         (3UL << ((pin) * 2))

#define GPIO_BSRR_SET_PIN(pin)        (1UL << (pin))
#define GPIO_BSRR_RESET_PIN(pin)      (1UL << ((pin) + 16))

// SysTick
// ARM Cortex-M4 core peripheral — same address on every Cortex-M4
#define SYSTICK_BASE 0xE000E010UL

typedef struct {
  __IO uint32_t CTRL;
  __IO uint32_t LOAD;
  __IO uint32_t VAL;
  __I uint32_t CALIB;
} SysTick_TypeDef;

#define SysTick ((SysTick_TypeDef *)SYSTICK_BASE)

// SysTick CTRL bits
#define SYSTICK_CTRL_ENABLE (1UL << 0)
#define SYSTICK_CTRL_TICKINT (1UL << 1)
#define SYSTICK_CTRL_CLKSOURCE (1UL << 2)
#define SYSTICK_CTRL_COUNTFLAG (1UL << 16)
#define SYSTICK_CTRL_CLKSOURCE (1UL << 2)

#define GPIOC_BASE 0x40020800UL
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define RCC_AHB1ENR_GPIOCEN (1UL << 2)

// DWT (Data Watchpoint and Trace)
// ARM Cortex-M4 core peripheral — same on every Cortex-M4
// Reference: ARM Cortex-M4 TRM section 9.2
#define DWT_BASE 0xE0001000UL
typedef struct {
  __IO uint32_t CTRL;
  __IO uint32_t CYCCNT;
} DWT_TypeDef;

#define DWT ((DWT_TypeDef *)DWT_BASE)

#define DWT_CTRL_CYCCNTENA (1UL << 0)

// CoreDebug
// Must enable CoreDebug before DWT works
#define CoreDebug_BASE 0xE000EDF0UL

typedef struct {
  __IO uint32_t DHCSR;
  __O uint32_t DCRSR;
  __IO uint32_t DCRDR;
  __IO uint32_t DEMCR;
} CoreDebug_TypeDef;

#define CoreDebug ((CoreDebug_TypeDef *)CoreDebug_BASE)

// CoreDebug_DEMCR bits
#define CoreDebug_DEMCR_TRCENA (1UL << 24) // enable DWT and ITM

#endif