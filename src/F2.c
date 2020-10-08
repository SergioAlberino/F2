/* Copyright 2020, Franco Bucafusco
 * All rights reserved.
 *
 * This file is part of sAPI Library.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*=====[Inclusions of function dependencies]=================================*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "sapi.h"
#include "keys.h"

/*=====[Definition & macros of public constants]==============================*/

/*=====[Definitions of extern global functions]==============================*/

// Prototipo de funcion de la tarea
void task_led0( void* taskParmPtr );
void task_led1( void* taskParmPtr );
void task_led2( void* taskParmPtr );
void task_led3( void* taskParmPtr );
void task_tecla( void* taskParmPtr );

/*=====[Definitions of public global variables]==============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
    BaseType_t res;

    // ---------- CONFIGURACIONES ------------------------------
    boardConfig();  // Inicializar y configurar la plataforma

    printf( "Ejercicio F2\n" );

    // Crear tareas en freeRTOS
    BaseType_t res0,res1,res2,res3;

    	// Crear tareas en freeRTOS
        res0 = xTaskCreate (
                  task_led0,						// Funcion de la tarea a ejecutar
                  ( const char * )"task_led0",	// Nombre de la tarea como String amigable para el usuario
                  configMINIMAL_STACK_SIZE*2,	// Cantidad de stack de la tarea
                  0,							// Parametros de tarea
                  tskIDLE_PRIORITY+1,			// Prioridad de la tarea
                  0								// Puntero a la tarea creada en el sistema
              );

        res1 = xTaskCreate (
                  task_led1,						// Funcion de la tarea a ejecutar
                  ( const char * )"task_led1",	// Nombre de la tarea como String amigable para el usuario
                  configMINIMAL_STACK_SIZE*2,	// Cantidad de stack de la tarea
                  0,							// Parametros de tarea
                  tskIDLE_PRIORITY+1,			// Prioridad de la tarea
                  0								// Puntero a la tarea creada en el sistema
              );

        res2 = xTaskCreate (
                  task_led2,						// Funcion de la tarea a ejecutar
                  ( const char * )"task_led2",	// Nombre de la tarea como String amigable para el usuario
                  configMINIMAL_STACK_SIZE*2,	// Cantidad de stack de la tarea
                  0,							// Parametros de tarea
                  tskIDLE_PRIORITY+1,			// Prioridad de la tarea
                  0								// Puntero a la tarea creada en el sistema
              );

        res3 = xTaskCreate (
                  task_led3,						// Funcion de la tarea a ejecutar
                  ( const char * )"task_led3",	// Nombre de la tarea como String amigable para el usuario
                  configMINIMAL_STACK_SIZE*2,	// Cantidad de stack de la tarea
                  0,							// Parametros de tarea
                  tskIDLE_PRIORITY+1,			// Prioridad de la tarea
                  0								// Puntero a la tarea creada en el sistema
              );

    	// Gestion de errores
    	if(res0 == pdFAIL||res1 == pdFAIL||res2 == pdFAIL||res3 == pdFAIL)
    	{
    		printf( "error" );
    		while(TRUE);						// VER ESTE LINK: https://pbs.twimg.com/media/BafQje7CcAAN5en.jpg
    	}

    /* inicializo driver de teclas */
    keys_Init();

    // Iniciar scheduler
    vTaskStartScheduler();					// Enciende tick | Crea idle y pone en ready | Evalua las tareas creadas | Prioridad mas alta pasa a running

    /* realizar un assert con "false" es equivalente al while(1) */
    configASSERT( 0 );
    return 0;
}

void task_led0( void* taskParmPtr )
{
    TickType_t dif_TEC1 =   pdMS_TO_TICKS( 500 );
    int tecla_presionada;
    TickType_t xPeriodicity = pdMS_TO_TICKS( 1000 ); // Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while( 1 )
    {

    	if( key_pressed(TEC1_INDEX ) )
        {
    		dif_TEC1 = get_diff(TEC1_INDEX);
        }

        gpioWrite( LEDB, ON );
        vTaskDelay(dif_TEC1);
        gpioWrite( LEDB, OFF );

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime, 2*dif_TEC1);
    }
}



void task_led1( void* taskParmPtr )
{
    TickType_t dif_TEC2 =   pdMS_TO_TICKS( 500 );
    int tecla_presionada;
    TickType_t xPeriodicity = pdMS_TO_TICKS( 1000 ); // Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while( 1 )
    {

    	if( key_pressed(TEC2_INDEX ) )
        {
    		dif_TEC2 = get_diff(TEC2_INDEX);
        }

        gpioWrite( LED1, ON );
        vTaskDelay(dif_TEC2);
        gpioWrite( LED1, OFF );

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime, 2*dif_TEC2);
    }
}

void task_led2( void* taskParmPtr )
{
    TickType_t dif_TEC3 =   pdMS_TO_TICKS( 500 );
    int tecla_presionada;
    TickType_t xPeriodicity = pdMS_TO_TICKS( 1000 ); // Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while( 1 )
    {

    	if( key_pressed(TEC3_INDEX ) )
        {
    		dif_TEC3 = get_diff(TEC3_INDEX);
        }

        gpioWrite( LED2, ON );
        vTaskDelay(dif_TEC3);
        gpioWrite( LED2, OFF );

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime, 2*dif_TEC3);
    }
}

void task_led3( void* taskParmPtr )
{
    TickType_t dif_TEC4 =   pdMS_TO_TICKS( 500 );
    int tecla_presionada;
    TickType_t xPeriodicity = pdMS_TO_TICKS( 1000 ); // Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while( 1 )
    {

    	if( key_pressed(TEC4_INDEX ) )
        {
    		dif_TEC4 = get_diff(TEC4_INDEX);
        }

        gpioWrite( LED3, ON );
        vTaskDelay(dif_TEC4);
        gpioWrite( LED3, OFF );

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime, 2*dif_TEC4);
    }
}


/* hook que se ejecuta si al necesitar un objeto dinamico, no hay memoria disponible */
void vApplicationMallocFailedHook()
{
    printf( "Malloc Failed Hook!\n" );
    configASSERT( 0 );
}

