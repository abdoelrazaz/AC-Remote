/*
 * main.c
 *
 *  Created on: May 30, 2024
 *      Author: Abdo
 */

#include "main.h"

u8 offFlag = 0;
u32 ovCounter=0;

void callback()
{
	ovCounter++;
	if(ovCounter == 4882)
	{
		offFlag = 1;
	}
}

int main(){


	GI_enable();
	SS_init();
	ADC_init();
	EEPROM_Init();
	TIMER0_initFastPwm();
	 u8 TempCurrent = TempCheck () ;
	 u8 Td ;

	DIO_setPinDir(DIO_PINA2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB4,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB5,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB3,DIO_OUTPUT);

	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PIND2,DIO_OUTPUT);

	TIMER0_initNormal();
	TIMER0_setCallbackOv(callback);
	TIMER0_start(TIMER0_DIV64);

	while (1){
		if (offFlag == 0){
			if (TempCurrent < Td ){
				// turn on heating  for lamp in protus
				DIO_setPinValue(DIO_PINA2,DIO_HIGH);
				// turn off for motor
				DIO_setPinValue(DIO_PINB4,DIO_LOW);
				DIO_setPinValue(DIO_PINB5,DIO_LOW);
				DIO_setPinValue(DIO_PINB3,DIO_LOW);

				//TIMER0_start(TIMER0_STOP);
			}
			else if(TempCurrent > Td) {
				DIO_setPinValue(DIO_PINA2,DIO_LOW);

				//TIMER0_start(TIMER0_DIV64);
				//TIMER0_setOcr((Tc*255)/(Tc+Td));

				DIO_setPinValue(DIO_PINB4,DIO_HIGH);
				DIO_setPinValue(DIO_PINB5,DIO_LOW);
				 }
			if (DIO_readPinValue(DIO_PIND2) == DIO_HIGH)
			{
				while(DIO_readPinValue(DIO_PIND2) == DIO_HIGH);
				Td ++;
				EEPROM_SendByte(Td,100);
			}

			else if (DIO_readPinValue(DIO_PIND3) == DIO_HIGH)
			{
				while(DIO_readPinValue(DIO_PIND3) == DIO_HIGH);
				Td --;
				EEPROM_SendByte(Td,100);
			}
		}
		else if (offFlag == 1){
			DIO_setPinValue(DIO_PINB4,DIO_LOW);
			DIO_setPinValue(DIO_PINB5,DIO_LOW);
			DIO_setPinValue(DIO_PINB3,DIO_LOW);
			DIO_setPinValue(DIO_PINA2,DIO_LOW);
		}
	}
	return 0;
}
