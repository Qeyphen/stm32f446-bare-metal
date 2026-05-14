#include "main.h"
#include "system_clock.h"
#include "dwt.h"

volatile uint32_t last_main_cycle  = 0;
volatile uint32_t first_isr_cycle  = 0;
volatile uint32_t latency_min      = 0xFFFFFFFF;
volatile uint32_t latency_max      = 0;
volatile uint32_t capture_count    = 0;
volatile uint32_t dwt_overhead     = 0;

void configure_tim2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    (void) RCC->APB1ENR;

    TIM2->PSC  = 89;
    TIM2->ARR  = 999;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->EGR  |= TIM_EGR_UG;
    TIM2->SR    = 0;
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1  |= TIM_CR1_CEN;
}

__attribute__((used)) void TIM2_IRQHandler(void) {
    first_isr_cycle = DWT_GetCycles();

    GPIOA->BSRR = GPIO_BSRR_SET_PIN(5);
    TIM2->SR    = 0;

    if (capture_count < 100) {
        uint32_t raw     = first_isr_cycle - last_main_cycle;
        uint32_t latency = (raw > dwt_overhead) ? (raw - dwt_overhead) : 0;
        if (latency < latency_min) latency_min = latency;
        if (latency > latency_max) latency_max = latency;
        capture_count++;
    }

    GPIOA->BSRR = GPIO_BSRR_RESET_PIN(5);
}

int main(void) {
    SystemClock_Config();
    DWT_Init();

    // calibrate DWT self-overhead before any other measurement
    volatile uint32_t cal_a = DWT_GetCycles();
    volatile uint32_t cal_b = DWT_GetCycles();
    dwt_overhead = cal_b - cal_a;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void) RCC->AHB1ENR;

    GPIOA->MODER &= ~GPIO_MODER_CLEAR(6);
    GPIOA->MODER |=  GPIO_MODER_MODE_OUTPUT(6);

    GPIOA->MODER &= ~GPIO_MODER_CLEAR(5);
    GPIOA->MODER |=  GPIO_MODER_MODE_OUTPUT(5);

    configure_tim2();

    while(1) {
        GPIOA->BSRR = GPIO_BSRR_SET_PIN(6);
        GPIOA->BSRR = GPIO_BSRR_RESET_PIN(6);
        last_main_cycle = DWT_GetCycles();
    }
}