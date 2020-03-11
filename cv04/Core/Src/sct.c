/*
 * sct.c
 *
 *  Created on: 19. 2. 2020
 *      Author: student
 */
#include "stm32f0xx.h"
#include "main.h"
#include "sct.h"


/*
#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)//PB5
#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10); } while (0)//PB10
#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4); } while (0)//PB4
#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3); } while (0)//PB3
*/
static const uint32_t reg_values[4][10] = {
		{    //PCDE--------GFAB @ DIS1
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
		},   {    //----PCDEGFAB---- @ DIS2
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
		},   {    //PCDE--------GFAB @ DIS3
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
		},  {   //----43215678---- @ DIS3
				0b0000000000000000 << 16,
				0b0000000100000000 << 16,
				0b0000001100000000 << 16,
				0b0000011100000000 << 16,
				0b0000111100000000 << 16,
				0b0000111110000000 << 16,
				0b0000111111000000 << 16,
				0b0000111111100000 << 16,
				0b0000111111110000 << 16,
				0b0000000000000000 << 16,
		}
};






void sct_init(void)
{
//	RCC->AHBENR |=RCC_AHBENR_GPIOBEN;
//	GPIOB->MODER |= GPIO_MODER_MODER3_0 |GPIO_MODER_MODER4_0 |GPIO_MODER_MODER5_0 | GPIO_MODER_MODER10_0;
	sct_led(0);
	HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_NOE_Pin, 0);
}

void sct_led(uint32_t value)
{
	uint32_t i;

	for(i=0;i<=31;i++)
	{

		if (value & 0x00000001)
		{
			HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_SDI_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_SDI_Pin, 0);
		}
		value >>= 1;

		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);


	}
	HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_value(uint16_t value1, uint8_t led)
{
 uint32_t reg=0;

	reg |= reg_values[0][value1 /100 % 10];
	reg |= reg_values[1][value1 /10 % 10];
	reg |= reg_values[2][value1 %10];
	reg |= reg_values[3][led];

	sct_led(reg);


}
