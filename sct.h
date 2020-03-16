/*
 * sct.h
 *
 *  Created on: 28. 2. 2020
 *      Author: student
 */

#ifndef SCT_H_
#define SCT_H_
#include "stm32f0xx.h"

void sct_init(void);

void sct_led(uint32_t value);
void sct_value(uint16_t value1, uint8_t led);



#endif /* SCT_H_ */
