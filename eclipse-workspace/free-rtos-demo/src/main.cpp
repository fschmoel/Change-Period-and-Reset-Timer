

/*
 * main.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Andreas Pretschner
 *
 */

#include <wiring.h>
#include<HardwareSerial.h>
//https://microcontrollerslab.com/use-freertos-arduino/
#include <Arduino_FreeRTOS.h>
#include <task.h>

static void MyTask1(void* pvParameters);
static void MyTask2(void* pvParameters);
static void MyTask3(void* pvParameters);
static void MyIdleTask(void* pvParameters);

void setup(){
//Initialize the Serial Monitor with 9600 baud rate
Serial.begin(9600);
Serial.println("In Setup function");
//Set the digital pins 8 to 11 as digital output pins
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);

//Create three tasks with labels Task1, Task2 and Task3 and assign the priority as 1, 2 and 3 respectively. +
//We also create the fourth task labeled as IdelTask when there is no task in
//operation and it has the highest priority.

 xTaskCreate(MyTask1, "Task1", 100, NULL, 3, NULL); //HIGH PRIO
 xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
 xTaskCreate(MyTask3, "Task3", 100, NULL, 1, NULL); //LOW PRIO
 xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);}

//We can change the priority of task according to our desire by changing the numeric’s //between NULL texts.

void loop(){
//There is no instruction in the loop section of the code.
// Because each task executes on interrupt after specified time
}

//The following function is Task1. We display the task label on Serial monitor.

static void MyTask1(void* pvParameters){

  while(1){
    digitalWrite(8,HIGH);

    digitalWrite(9,LOW);

    digitalWrite(10,LOW);

    digitalWrite(11,LOW);

    Serial.println("Task1");

    if (!digitalRead(7)){
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
  }
}

//Similarly this is task 2

static void MyTask2(void* pvParameters){
while(1)

  { digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    Serial.println("Task2");
    if (!digitalRead(6)){
        vTaskDelay(110/portTICK_PERIOD_MS);
    }
  }
}

//Similarly this is task 3

static void MyTask3(void* pvParameters){
while(1)
  {
   digitalWrite(8,LOW);
   digitalWrite(9,LOW);
   digitalWrite(10,HIGH);
   digitalWrite(11,LOW);
   Serial.println("Task3");
    if (!digitalRead(5)){
        vTaskDelay(120/portTICK_PERIOD_MS);
    }
  }
}

//This is the idle task which has the lowest priority and calls when no task is running.

static void MyIdleTask(void* pvParameters){
  while(1)
   {
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    Serial.println("Idle state");
        if (!digitalRead(4)){
            digitalWrite(8,HIGH);
            digitalWrite(9,HIGH);
            digitalWrite(10,HIGH);
            digitalWrite(11,LOW);
    }
    delay(50);
  }
}

int main(void){
   setup();
   loop();
   return(0);
}





