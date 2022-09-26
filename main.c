/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
void Button_1_Monitor (void *pvParameters);
void Button_2_Monitor (void *pvParameters);


int sys_time,cpu_load;
int time_in[7],time_out[7],time_total[7];




uint8_t B1_Rise=0;
uint8_t B1_Fall=0;
uint8_t B2_Rise=0;
uint8_t B2_Fall=0;
uint8_t Periodic_Status=0;


void Button_1_Monitor (void *pvParameters)
	
 {TickType_t xLastWakeTime=0;
	 uint8_t lastState=0;
	 uint8_t currentState=0;
	 while(1)
 { 
	 currentState=GPIO_read(PORT_1,PIN1);
		if(lastState==0 && currentState==1){
			B1_Rise=1;
			lastState=1;
		}
		else if(lastState==1 && currentState==0){
			B1_Fall=1;
			lastState=0;
		}	
			
	 
	 vTaskDelayUntil( &xLastWakeTime, 50);
	 
 }
	} 
 
	void Button_2_Monitor (void *pvParameters)
 {TickType_t xLastWakeTime=0;
	 uint8_t lastState=0;
	 uint8_t currentState=0;
	 while(1)
 {
	 	 currentState=GPIO_read(PORT_1,PIN2);
	 
		if(lastState==0 && currentState==1){
			B2_Rise=1;
			lastState=1;
		}
		else if(lastState==1 && currentState==0){
			B2_Fall=1;
			lastState=0;
		}	
			
	 vTaskDelayUntil( &xLastWakeTime, 50);
 }
	} 
 
	void Periodic_Transmitter (void *pvParameters)
 {TickType_t xLastWakeTime=0;
 while(1){
 
	 Periodic_Status=1;
 vTaskDelayUntil( &xLastWakeTime, 100);
 
 }
 
 }
 
 
 
 
 void Uart_Receiver (void *pvParameters)
 {TickType_t xLastWakeTime=0;
 while(1){
	 if(B1_Rise){
	 vSerialPutString("from button 1 rise \n",21);
	 B1_Rise=0;
	 }
	 if(B1_Fall){
		 vSerialPutString("from button 1 fall \n",21);
		 B1_Fall=0;
		 
	 }
	 if(B2_Rise){
		 vSerialPutString("from button 2 rise \n",21);
		 B2_Rise=0;
		 
	 }
	 if(B2_Fall){
		 vSerialPutString("from button 2 fall \n",21);
		 B2_Fall=0;
		 
	 }
	 if(Periodic_Status){
		 vSerialPutString("from periodic \n",16);
		 Periodic_Status=0;
		 
	 }
 
	 
 vTaskDelayUntil( &xLastWakeTime, 20);
 
 }
 }
 
 	void Load_1_Simulation (void *pvParameters)
 {TickType_t xLastWakeTime=0;
 while(1){
 int i;
	 for( i=0;i<33100;i++){
	 i=i;}
	 
	 
 vTaskDelayUntil( &xLastWakeTime, 10);
 
 }
 
 }
	void Load_2_Simulation (void *pvParameters)
 {TickType_t xLastWakeTime=0;
 while(1){
	int i;
	 for(i=0;i<79400;i++){
	 i=i;}
	 
 vTaskDelayUntil( &xLastWakeTime, 100);
 
 }
 
 }
	
 
int main( void )
{
	TaskHandle_t t1,t2,t3,t4,t5,t6;
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	
    /* Create Tasks here */
xTaskPeriodicCreate( Button_1_Monitor, ( const char * ) "Button_1_Monitor",configMINIMAL_STACK_SIZE, NULL,1, &t1, 50 );
 xTaskPeriodicCreate( Button_2_Monitor, ( const char * ) "Button_2_Monitor",configMINIMAL_STACK_SIZE, NULL,1, &t2, 50);
 xTaskPeriodicCreate( Periodic_Transmitter, ( const char * ) "Periodic_Transmitter",configMINIMAL_STACK_SIZE,NULL ,1, &t3, 100);
	xTaskPeriodicCreate( Uart_Receiver, ( const char * ) "Uart_Receiver",configMINIMAL_STACK_SIZE, NULL,1, &t4, 20);
	xTaskPeriodicCreate( Load_1_Simulation, ( const char * ) "Load_1_Simulation",configMINIMAL_STACK_SIZE, NULL,1, &t5, 10);
	xTaskPeriodicCreate( Load_2_Simulation, ( const char * ) "Load_2_Simulation",configMINIMAL_STACK_SIZE, NULL,1, &t6, 100);
	
	vTaskSetApplicationTaskTag(t1,(void*) 1);
	vTaskSetApplicationTaskTag(t2,(void*) 2);
	vTaskSetApplicationTaskTag(t3,(void*) 3);
	vTaskSetApplicationTaskTag(t4,(void*) 4);
	vTaskSetApplicationTaskTag(t5,(void*) 5);
	vTaskSetApplicationTaskTag(t6,(void*) 6);
 

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void){
GPIO_write(PORT_1, PIN0, PIN_IS_HIGH);
GPIO_write(PORT_1, PIN0, PIN_IS_LOW);
}
