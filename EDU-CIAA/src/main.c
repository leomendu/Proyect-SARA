/*==================[inclusions]=============================================*/
#include "../inc/main.h"
#include "../gen/proyecto.h"
#include "../inc/TimerTicks.h"
#include "sapi.h"       // <= sAPI header
#include <string.h>
#include <stdlib.h>
/*==================[macros and definitions]=================================*/

#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_MS		(TICKRATE_1MS)	/* 1000 ticks per second */
#define RX_BUFFER_SIZE	1024
#define MQTT_EVENT_FEED "feed"
#define MQTT_EVENT_FEEDRST "feedrst"
#define MQTT_EVENT_CONFIG "conf"
#define MQTT_EVENT_CONFIG_HMS "t"
#define MQTT_EVENT_CONFIG_SIZE 4
#define MQTT_EVENT_CONFIG_HMS_SIZE 1


/*==================[internal data declaration]==============================*/

volatile bool SysTick_Time_Flag = false; // @suppress("Type cannot be resolved")

/*! State machine definition */
static Proyecto statechart;

static char temp_string[RX_BUFFER_SIZE];

/*! This is a timed state machine that requires timer services */
#define NOF_TIMERS (sizeof(ProyectoTimeEvents)/sizeof(sc_boolean))

TimerTicks ticks[NOF_TIMERS];

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

CONSOLE_PRINT_ENABLE

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*! \file This header defines prototypes for all functions that are required
 *  by the state machine implementation.
 *
 *  This is a state machine uses time events which require access to a timing
 *  service. Thus the function prototypes:
 *  - blink_setTimer and
 *  - blink_unsetTimer
 *  are defined.
 *
 *  This state machine makes use of operations declared in the state machines
 *  interface or internal scopes. Thus the function prototypes:
 *  - blinkIface_opLED
 *  are defined.
 *
 *  These functions will be called during a 'run to completion step' (runCycle)
 *  of the statechart.
 *  There are some constraints that have to be considered for the
 *  implementation of these functions:
 *  - never call the statechart API functions from within these functions.
 *  - make sure that the execution time is as short as possible.
 */

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void proyecto_startMotor( Proyecto* handle){
	gpioWrite(LEDR, TRUE);
	gpioWrite(GPIO3, FALSE);
	gpioWrite(GPIO4, TRUE);
}

void proyecto_stopMotor( Proyecto* handle){
	gpioWrite(LEDR, FALSE);
	gpioWrite(GPIO3, FALSE);
	gpioWrite(GPIO4, FALSE);
}

void proyecto_opNotify( Proyecto* handle, sc_integer NOTIF){
	return;
}
sc_integer proyecto_opConfigureSec( Proyecto* handle, sc_integer intervalSec){
	return intervalSec;
}

void proyecto_opPause( Proyecto* handle){
	gpioWrite(LED3, !gpioRead(LED3));
}

void proyecto_opUnpause( Proyecto* handle){
	gpioWrite(LED3, FALSE);
}

/* Timer functions
*/
void proyecto_set_timer( Proyecto* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic )
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

void proyecto_unset_timer( Proyecto* handle, const sc_eventid evid )
{
	UnsetTimerTick( ticks, NOF_TIMERS, evid );
}

/* Hook on Handle interrupt from SysTick timer
*/
void myTickHook( void *ptr ) {

	/* The sysTick Interrupt Handler only sets a Flag */
	SysTick_Time_Flag = true;
}

/*  This function scans all EDU-CIAA-NXP buttons (TEC1, TEC2, TEC3 and TEC4),
 *  and return ID of pressed button (0001 for TEC1, 0010 for TEC2, 0101 for TEC3 and TEC1
 *  at the same time, 0000 if no button is pressed.
*/
uint32_t Buttons_GetStatus_(void) { // @suppress("Type cannot be resolved")
	uint8_t ret = false; // @suppress("Type cannot be resolved")
	uint32_t idx; // @suppress("Type cannot be resolved")

	for (idx = 0; idx < 4; ++idx) {
		if (gpioRead( TEC1 + idx ) == 0) // @suppress("Symbol is not resolved")
			ret |= 1 << idx;
	}
	return ret;
}

/* handler de la interrupcion por Rx */
void onRx(void *noUsado)
{
	int i = 0;
	memset(temp_string, 0, RX_BUFFER_SIZE*sizeof(char));

	do{
		temp_string[i] = uartRxRead(UART_GPIO);
		i++;
	} while(temp_string[i-1] != '\0' && i < RX_BUFFER_SIZE-1);

	printf("Recibimos \'%s\' por UART\r\n", temp_string);

//	while(strstr(temp_string, MQTT_EVENT_FEED)!=NULL){
//		proyecto_raise_evFeed(&statechart);
//		if(statechart.stateConfVector[SCVI_PROYECTO_MAIN_REGION_FEEDING]
//													  == Proyecto_main_region_Feeding)
//			break;
//	}

	if(strstr(temp_string, MQTT_EVENT_FEED)!=NULL)
		proyecto_raise_evFeed(&statechart);

	memset(temp_string, 0, RX_BUFFER_SIZE*sizeof(char));

}

int main(void)
{
	uint32_t i; // @suppress("Type cannot be resolved")

	uint32_t BUTTON_Status = 0; // @suppress("Type cannot be resolved")

	uint32_t BUTTON_Status_old; // @suppress("Type cannot be resolved")

	/* Generic initialization */
	boardConfig();

	/* Inicializar UART_232 como salida Serial de consola */
	consolePrintConfigUart( UART_GPIO, 115200 );
	consolePrintlnString( "UART_GPIO configurada a BDRATE: 115200." );

	/* Set de un callback al evento de Rx */
	uartCallbackSet(UART_GPIO, UART_RECEIVE, onRx, NULL);
	/* Habilito las interrupciones */
	uartInterrupt(UART_GPIO, true);

	/* Init Ticks counter => TICKRATE_MS */
	tickConfig( TICKRATE_MS );

	/* Add Tick Hook */
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Init Timer Ticks */
	InitTimerTicks( ticks, NOF_TIMERS );

	/* Statechart Initialization */
	proyecto_init( &statechart );
	proyecto_enter( &statechart );

	gpioInit(GPIO3, GPIO_OUTPUT);
	gpioInit(GPIO4, GPIO_OUTPUT);

	/* LED state is toggled in the main program */
	while (1) {
		/* The uC sleeps waiting for an interruption */

		//__WFI();

		/* When a interrupt wakes to the uC, the main program validates it,
		 * checking the waited Flag */
		if (SysTick_Time_Flag == true) {

			/* Then reset its Flag */
			SysTick_Time_Flag = false;

			/* Then Update all Timer Ticks */
			UpdateTimers( ticks, NOF_TIMERS );

			/* Then Scan all Timer Ticks */
			for (i = 0; i < NOF_TIMERS; i++) {

				/* Then if there are pending events */
				if (IsPendEvent( ticks, NOF_TIMERS, ticks[i].evid ) == true) {

					/* Then Raise an Event -> Ticks.evid => OK */
					proyecto_raise_time_event(&statechart, ticks[i].evid);

					/* Then Mark as Attached -> Ticks.evid => OK */
					MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
				}
			}

			/* Then Get status of buttons */
			BUTTON_Status_old = BUTTON_Status;
			BUTTON_Status = Buttons_GetStatus_();

			/* TEC1 => Feed
			 * TEC2 => FeedRst
			 * TEC3 => Pause (FOR DEBUGGING ONLY)
			 * TEC4 => Unpause (FOR DEBUGGING ONLY)*/
			if (BUTTON_Status == 1
					|| (strstr(temp_string, MQTT_EVENT_FEED)!=NULL)) {
				proyecto_raise_evFeed(&statechart);
			}

			if(statechart.stateConfVector[SCVI_PROYECTO_MAIN_REGION_FEEDING]
										  == Proyecto_main_region_Feeding)
				memset(temp_string, 0, RX_BUFFER_SIZE*sizeof(char));

			if ((BUTTON_Status == 0 && BUTTON_Status_old == 1))
				proyecto_raise_evIdle(&statechart);

			if (BUTTON_Status == 2 && BUTTON_Status_old == 0) {
				proyecto_raise_evFeedRst(&statechart);
			}

			if (BUTTON_Status == 4 && BUTTON_Status_old == 0) {
				consolePrintlnString("Feeding paused.");
				proyecto_raise_evPause(&statechart);
			}

			if (BUTTON_Status == 8 && BUTTON_Status_old == 0) {
				consolePrintlnString("Feeding resumed.");
				proyecto_raise_evUnpause(&statechart);
			}

//			if (strstr(temp_string, MQTT_EVENT_CONFIG) != NULL) {
//
//				//proyecto_raise_evConfigure(&statechart);
//
//				// if conf:hms -> change hour minute and seconds
//				uartInterrupt(UART_GPIO, false);
//
//				if(strstr(temp_string, MQTT_EVENT_CONFIG_HMS) != NULL) {
//
//					temp_string[MQTT_EVENT_CONFIG_SIZE+1
//								+MQTT_EVENT_CONFIG_HMS_SIZE+1+2] = '\0';
//					temp_string[MQTT_EVENT_CONFIG_SIZE+1
//								+MQTT_EVENT_CONFIG_HMS_SIZE+1+2+1+2] = '\0';
//					temp_string[MQTT_EVENT_CONFIG_SIZE+1
//								+MQTT_EVENT_CONFIG_HMS_SIZE+1+2+1+2+1+2] = '\0';
//
//					proyecto_set_viIntervalMin(&statechart,
//						(sc_integer)atoi(&temp_string[MQTT_EVENT_CONFIG_SIZE+1
//						+MQTT_EVENT_CONFIG_HMS_SIZE+1]));
//
//					proyecto_set_viIntervalMin(&statechart,
//						(sc_integer)atoi(&temp_string[MQTT_EVENT_CONFIG_SIZE+1
//						+MQTT_EVENT_CONFIG_HMS_SIZE+1+2+1]));
//
//					proyecto_set_viIntervalSec(&statechart,
//						(sc_integer)atoi(&temp_string[MQTT_EVENT_CONFIG_SIZE+1
//						+MQTT_EVENT_CONFIG_HMS_SIZE+1+2+1+2+1]));
//
//					proyecto_raise_evConfigure(&statechart);
//				}
//
//				// if conf:amo -> change amount of food
//
//				// this is due to RX buffer limits (16 bytes)
//
//				memset(temp_string, 0, RX_BUFFER_SIZE*sizeof(char));
//				uartInterrupt(UART_GPIO, true);
//			}
		}
	}
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
