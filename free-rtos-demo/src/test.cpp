#include <wiring.h>
#include<HardwareSerial.h>


#include <Arduino_FreeRTOS.h>
#include <timers.h>
#define mainAUTO_RELOAD_TIMER_PERIOD 	4000000/128000 // Definieren der Timer-Periode (500ms)
#define mainAUTO_RELOAD_TIMER_PERIOD2 	8000000/128000 // Definieren der Timer-Periode
#define BUTTON_PIN 4 // Pin für Taster
#define TIMER_RESET_WAIT 400000/128000 // Wartezeit für xTimerReset()

#ifndef INPUT_PULLUP
#define INPUT_PULLUP 0x2
#endif

TimerHandle_t xAutoReloadTimer;
BaseType_t xTimer2Started;


static void prvTimerCallback( TimerHandle_t xTimer );


void setup()
{
Serial.begin(115200); // Enable serial communication library.
pinMode(BUTTON_PIN, INPUT_PULLUP);

xAutoReloadTimer = xTimerCreate(
/* Text name for the software timer - not used by FreeRTOS. */
"AutoReload",
/* The software timer's period in ticks. */
mainAUTO_RELOAD_TIMER_PERIOD,
/* Setting uxAutoRealod to pdTRUE creates an auto-reload timer. */
pdTRUE,
/* This example does not use the timer id. */
0,
/* The callback function to be used by the software timer being created. */
prvTimerCallback);
/* Check the software timers were created. */
if(( xAutoReloadTimer != NULL ) )
{
/* Start the software timers, using a block time of 0 (no block time). The scheduler has
not been started yet so any block time specified here would be ignored anyway. */
xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );
/* The implementation of xTimerStart() uses the timer command queue, and xTimerStart()
will fail if the timer command queue gets full. The timer service task does not get
created until the scheduler is started, so all commands sent to the command queue will
stay in the queue until after the scheduler has been started. Check both calls to
xTimerStart() passed. */
if( ( xTimer2Started == pdPASS ) )
{
/* Start the scheduler. */
vTaskStartScheduler();
}
}
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == HIGH) { // Überprüfe ob Taster gedrückt ist (aktiv HIGH wegen Pullup)
	  Serial.println("Taster gedrückt, Timer wird zurückgesetzt..."); // Ausgabe einer Meldung über die serielle Schnittstelle
	  BaseType_t xResetStatus = xTimerReset(xAutoReloadTimer, TIMER_RESET_WAIT); // Zurücksetzen des Timers

	  if (xResetStatus == pdPASS) { // Überprüfen, ob Timer erfolgreich zurückgesetzt wurde
		  Serial.println("Timer erfolgreich zurückgesetzt!"); // Ausgabe einer Bestätigungsmeldung
	  } else {
		  Serial.println("Timer-Reset fehlgeschlagen!"); // Ausgabe einer Fehlermeldung
	  }
	  while (digitalRead(BUTTON_PIN) == HIGH); // Warten, bis Taster losgelassen wird (Entprellung)

  }
}

static void prvTimerCallback( TimerHandle_t xTimer )
{
TickType_t xTimeNow;
uint32_t ulExecutionCount;
/* A count of the number of times this software timer has expired is stored in the timer's
ID. Obtain the ID, increment it, then save it as the new ID value. The ID is a void
pointer, so is cast to a uint32_t. */
ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
ulExecutionCount++;
vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );
/* Obtain the current tick count. */
xTimeNow = xTaskGetTickCount();
/* The handle of the one-shot timer was stored in xOneShotTimer when the timer was created.
Compare the handle passed into this function with xOneShotTimer to determine if it was the
one-shot or auto-reload timer that expired, then output a string to show the time at which
the callback was executed. */

Serial.print("Auto-reload timer callback executing ");
Serial.println( xTimeNow/31 );
if( ulExecutionCount >= 5 )
{
xTimerChangePeriod( xAutoReloadTimer, /* The timer being updated. */
mainAUTO_RELOAD_TIMER_PERIOD2, /* The new period for the timer. */
0 ); /* Do not block when sending this command. */
}
}



int main(void){

	setup();
	for(;;){
		loop();

	}
return(0);
}
