////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////THIS CODE IS OWNED BY CONQUISTOR EMPIRE OF/////////////////////////
/////////////////////////////////////HIJOS DEL MURILLO//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void Delay(uint32_t);

uint32_t FS=120000000;
volatile uint32_t count1=0;
volatile uint32_t count2=0;
volatile uint32_t count3=0;

/*----------INTERRUPT A0----------*/
void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	count1++;
	if((count1 % 2) != 1)
	{
		GPIOPinWrite(GPIO_PORTN_BASE, 0x01, 0x01);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTN_BASE, 0x01, 0x00);
	}
}

/*----------INTERRUPT A1----------*/
void Timer1IntHandler(void)
{
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	
	count2++;
	if((count2 % 2) != 1)
	{
		GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0x02);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0x00);
	}
}

/*----------INTERRUPT A2----------*/
void Timer2IntHandler(void)
{
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	
	count3++;
	if((count3 % 2) != 1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x10);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x01);
	}
}

int main(void)
{
	/*----------CLOCK DECLARATION----------*/
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
	
	/*----------GPIO CLOCK ACTIVATION----------*/    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	/*----------GPIO DECLARATION----------*/
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);
	
	/*----------INTERRUPTS DECLARATION----------*/
	IntMasterEnable();

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, FS*1);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
	IntEnable(INT_TIMER0A);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER1_BASE, TIMER_A, FS*3);
	TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER1_BASE, TIMER_A);
	IntEnable(INT_TIMER1A);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER2_BASE, TIMER_A, FS*0.1);
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER2_BASE, TIMER_A);
	IntEnable(INT_TIMER2A);
	
	while(1)
	{		
		/*----------WHILE EMPTY----------*/
	}
}

void Delay(uint32_t time){
	SysCtlDelay(40000*time);
}