/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f0xx.h"
#include "sct.h"

int main (void)
{
	sct_init();
	sct_led(0x7A5C36DE);
	for (volatile uint32_t j=0; j<300000; j++) {}

	uint16_t count=0;
	while(1) {
		sct_value(count);

		for (volatile uint32_t j=0; j<300000; j++) {}
		if (count==999)	{
			count=0;
		}else{
			count+=111;
		}
	}
}
