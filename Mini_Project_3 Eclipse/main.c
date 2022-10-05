/******************************************************************************
*  File name:		main.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#include "adc.h"
#include "lcd.h"
#include "motor.h"
#include "lm35_sensor.h"

/* Structure to dynamic configure the ADC module */
ADC_ConfigType ADC_Configration = {ADC_INTERNAL_VREF,ADC_F_CPU_8};

/* global variable to store the temperature value */
uint8 g_tempValue ;

/*******************************************************************************
* Function Name:		displayTemp
* Description:			Function to handle different cases of temperature values on the LCD
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void displayTemp()
{
	if(g_tempValue >= 100)
	{
		LCD_moveCursor(1, 10);
		LCD_intgerToString(g_tempValue);
	}
	else
	{
		LCD_moveCursor(1, 10);
		LCD_intgerToString(g_tempValue);
		LCD_displayCharacter(' ');
	}
}


int main(void)
{
	/* Initializing different modules */
	ADC_init(&ADC_Configration) ;
	LCD_init();
	DcMotor_Init();

	/* Displaying outputs on the LCD */
	LCD_displayStringRowColumn(0, 3, "Fan is    ");
	LCD_displayStringRowColumn(1, 3, "Temp =    C");

	/* Calculate the temperature value and store it in a global variable */
	g_tempValue = LM35_getTemperature();

	while(1)
	{
		g_tempValue = LM35_getTemperature();
		displayTemp();

		if(g_tempValue >= 120)
		{
			/* Temperature >= 120 -> Fan is ON  with 100% of its speed */
			LCD_displayStringRowColumn(0, 10, "ON ");
			DcMotor_Rotate(DcMotor_CW, 100);
		}
		else if(g_tempValue >= 90)
		{
			/* Temperature >= 90 -> Fan is ON  with 75% of its speed */
			LCD_displayStringRowColumn(0, 10, "ON ");
			DcMotor_Rotate(DcMotor_CW, 75);
		}
		else if(g_tempValue >= 60)
		{
			/* Temperature >= 60 -> Fan is ON  with 50% of its speed */
			LCD_displayStringRowColumn(0, 10, "ON ");
			DcMotor_Rotate(DcMotor_CW, 50);
		}
		else if(g_tempValue >= 30)
		{
			/* Temperature >= 30 -> Fan is ON  with 25% of its speed */
			LCD_displayStringRowColumn(0, 10, "ON ");
			DcMotor_Rotate(DcMotor_CW, 25);
		}
		else
		{
			/* Temperature >= 60 -> Fan is OFF */
			LCD_displayStringRowColumn(0, 10, "OFF ");
			DcMotor_Rotate(DcMotor_STOP, 0);
		}

	}
}
