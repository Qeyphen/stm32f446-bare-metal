#ifndef DWT_H
#define DWT_H

#include "main.h"

static inline void DWT_Init(void) {
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA;
}

// Reset counter
static inline void DWT_Reset(void) {
  DWT->CYCCNT = 0;
}

// Read current cycles
static inline uint32_t DWT_GetCycles(void) {
  return DWT->CYCCNT;
}

static inline uint32_t DWT_ElapsedCycles(uint32_t start) {
    return DWT->CYCCNT - start;
}

#endif