#ifndef STM32F446XX_H
#define STM32F446XX_H

#include <stdint.h>

#define __IO volatile
#define __I  volatile const
#define __O  volatile

// The register layouts and associated definitions are derived from the
// STM32F446xx Reference Manual (RM0390):
// https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx.pdf

// ========================== RCC ==========================
#define RCC_BASE 0x40023800UL

typedef struct {
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t      RESERVED0;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
  uint32_t      RESERVED1;
  uint32_t      RESERVED2;
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t      RESERVED3;
  __IO uint32_t APB1ENR;
  __IO uint32_t APB2ENR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef*) RCC_BASE)

#define RCC_AHB1ENR(pin)   (1UL << (pin))
#define RCC_APB1ENR_TIM2EN (1UL << 0)

#define RCC_CR_HSEON  (1UL << 16)
#define RCC_CR_HSERDY (1UL << 17)
#define RCC_CR_PLLON  (1UL << 24)
#define RCC_CR_PLLRDY (1UL << 25)

#define RCC_APB1ENR_PWREN   (1UL << 28)
#define RCC_AHB1ENR_GPIOAEN (1UL << 0)

#define RCC_CFGR_HPRE_DIV1  (0UL << 4)
#define RCC_CFGR_PPRE1_DIV4 (5UL << 10)
#define RCC_CFGR_PPRE2_DIV2 (4UL << 13)
#define RCC_CFGR_SWS_PLL    (2UL << 2)
#define RCC_CFGR_SW_PLL     (2UL << 0)
#define RCC_CFGR_SWS_Msk    (3UL << 2)

#define RCC_CFGR_HPRE_Msk  (0xFUL << 4U)
#define RCC_CFGR_PPRE1_Msk (0x7UL << 10U)
#define RCC_CFGR_PPRE2_Msk (0x7UL << 13U)

#define RCC_PLLCFGR_PLLM_Pos   0U
#define RCC_PLLCFGR_PLLN_Pos   6U
#define RCC_PLLCFGR_PLLP_Pos   16U
#define RCC_PLLCFGR_PLLQ_Pos   24U
#define RCC_PLLCFGR_PLLSRC_HSE (1UL << 22)

// ========================== TIM2 ==========================
#define TIM2_BASE 0x40000000UL

typedef struct {
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMCR;
  __IO uint32_t DIER;
  __IO uint32_t SR;
  __IO uint32_t EGR;
  __IO uint32_t CCMR1;
  __IO uint32_t CCMR2;
  __IO uint32_t CCER;
  __IO uint32_t CNT;
  __IO uint32_t PSC;
  __IO uint32_t ARR;
} TIM2_TypeDef;

#define TIM2 ((TIM2_TypeDef*) TIM2_BASE)

// TIM2 Control Register 1 (CR1)
#define TIM_CR1_CEN (1U << 0)

// TIM2 DMA/Interrupt Enable Register (DIER)
#define TIM_DIER_UIE (1U << 0) // Update interrupt enable

// TIM2 Status Register (SR)
#define TIM_SR_UIF      (1U << 0) // Update interrupt flag
#define TIM2_SR_UIF_MSK (1U << 0) // Update interrupt flag mask (legacy)

// TIM2 Event Generation Register (EGR)
#define TIM_EGR_UG (1U << 0) // Update generation

// TIM2 Capture/Compare Mode Register 1 (CCMR1)
#define TIM_CCMR1_OC1M_MSK (7U << 4)
#define TIM_CCMR1_OC1M_PWM (6U << 4)
#define TIM_CCMR1_OC1PE    (1U << 3)

// TIM2 Capture/Compare Enable Register (CCER)
#define TIM_CCER_CC1E (1U << 0)

// ========================== PWR ==========================
#define PWR_BASE 0x40007000UL

typedef struct {
  __IO uint32_t CR;
  __IO uint32_t CSR;
} PWR_TypeDef;

#define PWR ((PWR_TypeDef*) PWR_BASE)

#define PWR_CR_VOS (3 << 14)

// ========================== FLASH ==========================
#define FLASH_BASE 0x40023C00UL

typedef struct {
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t OPTCR;
} FLASH_TypeDef;

#define FLASH ((FLASH_TypeDef*) FLASH_BASE)

#define FLASH_ACR_LATENCY     (5 << 0)
#define FLASH_ACR_PRFTEN      (1UL << 8)
#define FLASH_ACR_ICEN        (1UL << 9)
#define FLASH_ACR_DCEN        (1UL << 10)
#define FLASH_ACR_LATENCY_5WS (5UL << 0)

// ========================== GPIOA ==========================
#define GPIOA_BASE 0x40020000UL

typedef struct {
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __I uint32_t  IDR;
  __IO uint32_t ODR;
  __O uint32_t  BSRR;
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)

#define GPIOA_AFR_CLEAR(pin)   (0xFU << ((pin) * 4))
#define GPIOA_AFR_SET(pin, af) ((af) << ((pin) * 4))
#define GPIO_AFR_SET(pin, af)  ((af) << ((pin) * 4))

#define GPIO_MODER_MODE_OUTPUT(pin) (1UL << ((pin) * 2))
#define GPIO_MODER_AF(pin)          (2UL << ((pin) * 2))
#define GPIO_MODER_CLEAR(pin)       (3UL << ((pin) * 2))

#define GPIO_BSRR_SET_PIN(pin)   (1UL << (pin))
#define GPIO_BSRR_RESET_PIN(pin) (1UL << ((pin) + 16))

// ========================== SysTick ==========================
#define SYSTICK_BASE 0xE000E010UL

typedef struct {
  __IO uint32_t CTRL;
  __IO uint32_t LOAD;
  __IO uint32_t VAL;
  __I uint32_t  CALIB;
} SysTick_TypeDef;

#define SysTick ((SysTick_TypeDef*) SYSTICK_BASE)

#define SYSTICK_CTRL_ENABLE    (1UL << 0)
#define SYSTICK_CTRL_TICKINT   (1UL << 1)
#define SYSTICK_CTRL_CLKSOURCE (1UL << 2)
#define SYSTICK_CTRL_COUNTFLAG (1UL << 16)

// ========================== GPIOC ==========================
#define GPIOC_BASE 0x40020800UL
#define GPIOC      ((GPIO_TypeDef*) GPIOC_BASE)

#define RCC_AHB1ENR_GPIOCEN (1UL << 2)

// ========================== DWT ==========================
#define DWT_BASE 0xE0001000UL

typedef struct {
  __IO uint32_t CTRL;
  __IO uint32_t CYCCNT;
} DWT_TypeDef;

#define DWT ((DWT_TypeDef*) DWT_BASE)

#define DWT_CTRL_CYCCNTENA (1UL << 0)

// ========================== CoreDebug ==========================
#define CoreDebug_BASE 0xE000EDF0UL

typedef struct {
  __IO uint32_t DHCSR;
  __O uint32_t  DCRSR;
  __IO uint32_t DCRDR;
  __IO uint32_t DEMCR;
} CoreDebug_TypeDef;

#define CoreDebug ((CoreDebug_TypeDef*) CoreDebug_BASE)

#define CoreDebug_DEMCR_TRCENA (1UL << 24)

// ========================== NVIC ==========================
#define NVIC_BASE 0xE000E100UL

typedef struct {
  __IO uint32_t ISER[8U];
  uint32_t      RESERVED0[24U];
  __IO uint32_t ICER[8U];
  uint32_t      RESERVED1[24U];
  __IO uint32_t ISPR[8U];
  uint32_t      RESERVED2[24U];
  __IO uint32_t ICPR[8U];
  uint32_t      RESERVED3[24U];
  __IO uint32_t IABR[8U];
  uint32_t      RESERVED4[56U];
  __IO uint8_t  IP[240U];
  uint32_t      RESERVED5[644U];
  __O uint32_t  STIR;
} NVIC_TypeDef;

#define NVIC ((NVIC_TypeDef*) NVIC_BASE)

// ========================== IRQ Numbers ==========================
typedef enum {
  // Cortex-M4 Core Interrupts
  HardFault_IRQn = -13,
  MemoryManagement_IRQn = -12,
  BusFault_IRQn = -11,
  UsageFault_IRQn = -10,

  // STM32F446 Peripheral Interrupts
  TIM2_IRQn = 28,

} IRQn_Type;

// Enable interrupt in NVIC
static inline void NVIC_EnableIRQ(IRQn_Type IRQn) {
  if ((int32_t) (IRQn) >= 0) {
    NVIC->ISER[(((uint32_t) IRQn) >> 5UL)] = (uint32_t) (1UL << (((uint32_t) IRQn) & 0x1FUL));
  }
}

// Disable interrupt in NVIC
static inline void NVIC_DisableIRQ(IRQn_Type IRQn) {
  if ((int32_t) (IRQn) >= 0) {
    NVIC->ICER[(((uint32_t) IRQn) >> 5UL)] = (uint32_t) (1UL << (((uint32_t) IRQn) & 0x1FUL));
  }
}

// Set interrupt priority
static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) {
  if ((int32_t) (IRQn) >= 0) {
    NVIC->IP[((uint32_t) IRQn)] = (uint8_t) ((priority << 4U) & 0xFFU);
  }
}

#endif