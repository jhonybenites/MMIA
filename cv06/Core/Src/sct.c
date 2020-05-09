/*
 * sct.c
 *
 *  Created on: 19. 2. 2020
 *      Author: student
 */

/* sct2024 ----- pin
 *	 SDI - ED5 - PB4
 * 	 CLK - ED3 - PB3
 *   nLA - ED4 - PB5
 *   nOE - ED6 - PB10
 *
 *
 */

#include "stm32f0xx.h"

#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)

#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3); } while (0)

#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4); } while (0)

#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10); } while (0)

void sct_led(uint32_t value);


void sct_init(void)
{

		RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable
		GPIOB->MODER |= GPIO_MODER_MODER4_0; //  SDI = PB4, output
		GPIOB->MODER |= GPIO_MODER_MODER5_0; //  nLA = PB5, output
		GPIOB->MODER |= GPIO_MODER_MODER3_0; //  CLK = PB3, output
		GPIOB->MODER |= GPIO_MODER_MODER10_0; // nOE = PB10, output

		sct_led(0); // write zeros

		sct_noe(0); // output enable

		sct_clk(0); // clk 0

		sct_nla(1);
}

void sct_led(uint32_t value)
{

	for(uint16_t index = 0; index < 32; index ++)
	{
		if ((value >> index) & 0x00000001)
		{
			sct_sdi(1);
		}
		else
		{
			sct_sdi(0);
		}

		sct_clk(1);

		sct_clk(0);

	}

	 sct_nla(0);
	 sct_nla(1);

}

void sct_value(uint16_t value)
{

	uint32_t reg = 0x00000000;

	static const uint32_t reg_values[3][10] =
	{
			{
					//PCDE--------GFAB @ DIS1
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
			},
			{
					//----PCDEGFAB---- @ DIS2
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
			},
			{
					//PCDE--------GFAB @ DIS3
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
			},
	};

	reg |= reg_values[0][value / 100 % 10];

	reg |= reg_values[1][value / 10 % 10];

	reg |= reg_values[2][value / 1 % 10];

	sct_led(reg);


}

