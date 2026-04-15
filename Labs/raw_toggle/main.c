#include "main.h"
#include "system_clock.h"
#include "dwt.h"

volatile float    cycles_per_iter = 0.0f;
volatile float    ns_per_iter     = 0.0f;
volatile uint32_t total_cycles    = 0;

#define ITR         1000UL
#define SYSCLK_HZ   180000000UL

int main(void)
{
    SystemClock_Config();
    DWT_Init();

    RCC->AHB1ENR |= (1UL << 0);
    (void)RCC->AHB1ENR;
    
    GPIOA->MODER &= ~GPIO_MODER_CLEAR(5);
    GPIOA->MODER |=  GPIO_MODER_MODE_OUTPUT(5);

    // warm up — let pipeline settle before measuring
    for (uint32_t i = 0; i < 100; i++) {
        GPIOA->BSRR = GPIO_BSRR_SET_PIN(5) | GPIO_BSRR_RESET_PIN(5);
    }

    uint32_t start = DWT_GetCycles();
    for (uint32_t i = 0; i < ITR; i++) {
        GPIOA->BSRR = (1UL << 5) | (1UL << 21);
    }
    total_cycles = DWT_ElapsedCycles(start);

    cycles_per_iter = (float)total_cycles / (float)ITR;
    ns_per_iter = cycles_per_iter * (1000000000.0f / 180000000.0f);
    
    while(1) {}
}

/// CFLAGS += -O0
// ART OFF 
// cycles_per_iter = 24.0620003
// ns_per_iter = 133.67778
// total_cycles = 24062

// ART ON
// cycles_per_iter = 17.0499992
// ns_per_iter = 94.7222137
// total_cycles = 17050

/// CFLAGS += -O1
// ART OFF 
// cycles_per_iter = 13.0100002
// ns_per_iter = 72.2777786
// total_cycles = 13010

// ART ON
// cycles_per_iter = 4.0170002
// ns_per_iter = 22.3166676
// total_cycles = 4017

/// CFLAGS += -O2
// ART OFF 
// cycles_per_iter = 14.0030003
// ns_per_iter = 77.7944412
// total_cycles = 14003

// ART ON
// cycles_per_iter = 4.02199984
// ns_per_iter = 22.3444424
// total_cycles = 4022