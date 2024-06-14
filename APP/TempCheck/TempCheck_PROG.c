/*
 * TempCheck_PROG.c
 *
 *  Created on: May 30, 2024
 *      Author: Abdo
 */

#include "TempCheck_INT.h"
void init_TempCheck (){
	ADC_init();

	DIO_setPinDir(DIO_PINA1, DIO_INPUT);


}

f32 TempCheck () {


u32	VDigitalTemp = ADC_read(ADC_CH1);
	f32	VAnalogTemp = (ADC_convertAnalog(VDigitalTemp))*100;

	return VAnalogTemp ;




}
