#include "stupid_delay.h"
#include "hal_pll.h"

#define MAGIC_KOEF_FOR_ONE_MS (HAL_PLL_GetRealCoreClock() / 30)

// -----------------------------------------------------------------------------
void StupidDelayMs(unsigned int ms) {
	// HAL_PLL_GetRealCoreClock returns value in KHz
	// multiply to 1000 that convert to Hz and than divide to 1000
	// that convert to ticks per miliseconds
	unsigned int ticks = ms * MAGIC_KOEF_FOR_ONE_MS;
	while (--ticks);
}
