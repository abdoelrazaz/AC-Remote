/*
 * SS_INT.h
 *
 *  Created on: May 30, 2024
 *      Author: Abdo
 */

#ifndef HAL_SS_SS_INT_H_
#define HAL_SS_SS_INT_H_
#include "STD_TYPES.h"

//Config
#define SS_S0	DIO_PINA4
#define SS_S1	DIO_PINA5
#define SS_S2	DIO_PINA6
#define SS_S3	DIO_PINA7
#define SS_ENABLE1	DIO_PINB1
#define SS_ENABLE2	DIO_PINB2


void SS_init();
void SS_writeNum(u8 num);

#endif /* HAL_SS_SS_INT_H_ */
