#include "timer.h"

void configure_timer(uint8_t i) {
  switch (i) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 12:
    case 13:
    case 14:
      RCC->APB1ENR |= RCC_APB1ENR(0);
  }
}