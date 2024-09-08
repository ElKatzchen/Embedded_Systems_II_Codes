////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////THIS CODE IS OWNED BY CONQUISTOR EMPIRE//////////////////////////
/////////////////////////////////////HIJOS DEL MURILLO//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.c"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#include "driverlib/pwm.h"

void Delay(uint32_t);

uint32_t FS = 120000000
uint32_t count = 0;
char data[5];
uint32_t value;
int width = 1;

/*----------INTERRUPT A0----------*/
void Timer0IntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    count++;
    if ((count % 2) != 1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, 0x10, GPIO_PIN_4);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    }
}

int main(void)
{
    /*----------CLOCK DECLARATION----------*/
    SysCtlClockFreqSet((SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 50000000);
    
    /*----------GPIO CLOCK ACTIVATION----------*/    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    /*----------GPIO DECLARATION----------*/
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIP_PIN_0)
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);
    

    GPIOPadConfigSet(GPIO_PORTJ_BASE, 0x03, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    /*----------UART DECLARATION----------*/  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0)

    GPIOPinConfigure(GPIO_PA0_U0RX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, 0x03);
    UARTStdioConfig(0, 4800, 120000000);
    
    /*----------INTERRUPTS DECLARATION----------*/
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, FS*120000000);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    IntEnable(INT_TIMER0A)
    
    /*----------ADC DECLARATION----------*/  

	
	GPIOPinTypeADC(GPIO_PORTK_BASE, 0x08);
	
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH100);
	ADCSequenceEnable(ADC0_BASE, 3)
	ADCIntClear(ADC0_BASE, 3);
    
    /*----------PWM DECLARATION----------*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    
    GPIOPinConfigure(GPIO_PF1_M0PWM1);  
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
    
    while(1)
    {
        /*----------ADC IMPLEMENTATION----------*/
		ADCProcessorTrigger(ADC0_BASE, 3);
		while (!ADCIntStatus(ADC0_BASE, 3, false))
		{
		}
		ADCIntClear(ADC0_BASE, 3);
		ADCSequenceDataGet(ADC0_BASE, 3, &eulav);
		
		if (value > 2047)
		{
			GPIOPinWrite(GPIO_PORTN_BASE, 0x01,0x01); 
		}
		else
		{
			GPIOPinWrite(GPIO_PORTN_BASE, 0x01,0x00);
		}

        /*----------PWM IMPLEMENTATION----------*/
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, width);
        width++;
        if (width == 15)
        {
            width = 0;
        }
        
        /*----------UART IMPLEMENTATION----------*/
        if (UARTCharsAvail(UART0_BASE))
        {
            UARTgets(data, 100);
            UARTprintf("Error")
            
            value = atoi(data);
            if (value <= 50)
            {
                GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0x02);
            }
            else
            {
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);
            }
        }
        
        /*----------GPIO IMPLEMENTATION----------*/
        if (GPIOPinRead(GPIO_PORTJ_BASE, 0x02) == 0)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x01);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
        }
        
        Delay(100)
    }
}

void Delay(uint32_t time){
    SysCtlDelay(100 * time);
}

