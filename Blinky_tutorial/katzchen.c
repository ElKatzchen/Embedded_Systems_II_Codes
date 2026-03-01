////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////THIS CODE IS OWNED BY CONQUISTOR EMPIRE//////////////////////////
/////////////////////////////////////HIJOS DEL MURILLO//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void Delay(uint32_t);

uint32_t FS=120000000;

int main(void)
{
	/*----------CLOCK DECLARATION----------*/
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
	
	/*----------GPIO CLOCK ACTIVATION----------*/    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	/*----------GPIO DECLARATION----------*/
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);

	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, 0x03); 	
	GPIOPadConfigSet(GPIO_PORTJ_BASE, 0x03, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	while(1)
	{		
		/*----------GPIO IMPLEMENTATION----------*/
		if(GPIOPinRead(GPIO_PORTJ_BASE, 0x02)==0)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, 0x01, 0x01);
			GPIOPinWrite(GPIO_PORTN_BASE, 0x01, 0x01);
		}
		else if(GPIOPinRead(GPIO_PORTJ_BASE, 0x01)==0)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, 0x10, 0x10);
			GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0x02);
		}
		else
		{
			GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00);
			GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
		}
	}
}

void Delay(uint32_t time){
	SysCtlDelay(40000*time);
}



//   Pin     7 6 5 4 || 3 2 1 0
//  Binary   1 0 1 0 || 0 0 1 1
//    0x        A    ||    3

//   Pin     7 6 5 4 || 3 2 1 0
//  Binary   1 1 1 1 || 1 0 0 1
//    0x        F    ||    9

//   Pin     7 6 5 4 || 3 2 1 0
//  Binary   1 1 1 0 || 1 1 0 1
//    0x        E    ||    D

//   Pin     7 6 5 4 || 3 2 1 0
//  Binary   0 1 1 0 || 1 0 1 0
//    0x        6    ||    A

//   Pin     7 6 5 4 || 3 2 1 0
//  Binary   1 0 1 1 || 0 1 0 0
//    0x        B    ||    4