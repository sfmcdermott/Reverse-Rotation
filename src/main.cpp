#include <Arduino.h>


#define INTERVAL_OUTPUT1 5000              //These set the pulse interval of the outputs, 5000us=5ms=200hz 
#define INTERVAL_OUTPUT2 5000              
 
unsigned long time_1 = 0;                 //Pulse the first output on startup
unsigned long time_2 = time_1 + 2000;   //This is the delay for the second output from when the first output has activated
unsigned int On1Time = 1248;              //This is the width of the output pulses
unsigned int On2Time = 2496;              //Because the nano is 8mhz the micros() value increments in multiples of 8, so everything has to be a multiple of 8

int OutputPins[] = {9,10};
int InputPins[] = {3,4,5,6};





void setup() {
for (unsigned int i = 0; (i <= sizeof(InputPins)); i++){                          //Cycle through the array of input pins and set them to INPUT_PULLUP
  pinMode(InputPins[i], INPUT_PULLUP);}

for (unsigned int i = 0; (i <= sizeof(OutputPins)); i++){                         //Cycle through the array of output pins and set them to OUTPUT, write them low at the same time
  pinMode(OutputPins[i], OUTPUT);
  digitalWrite(OutputPins[i],LOW);}
}


void loop() {
   if(digitalRead(InputPins[0])==LOW){
   
                                                                                  //micros() counts up from initial powerup
    if(micros() >= time_1 + INTERVAL_OUTPUT1){                                    //Check if current micros() is greater or equal to the first time target
        time_1 +=INTERVAL_OUTPUT1;                                                //Add the interval to the target time
        digitalWrite(OutputPins[0],HIGH);                                         //Turn on Digital Out 1
    }

    if (digitalRead(OutputPins[0]) == HIGH){                                      //If the first output is on
      if(micros() >= time_1 + On1Time){digitalWrite(OutputPins[0], LOW);}         //Check if its been turned on for the desired amount of time, if it has, turn it off
    }

                                                                                  //Repeat for output 2
    if(micros() >= time_2 + INTERVAL_OUTPUT2){
        time_2 +=INTERVAL_OUTPUT2;
        digitalWrite(OutputPins[1], HIGH);
    }
    if(digitalRead(OutputPins[1]) == HIGH){
      if(micros() >= time_2 + On2Time){digitalWrite(OutputPins[1], LOW);}
    }
   }

  

}