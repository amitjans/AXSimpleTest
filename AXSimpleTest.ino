/***************************
 * AXSimpleTest
 * This sketch sends positional commands to the AX servo 
 * attached to it - the servo must set to ID # 1
 * The sketch will send a value, i, to the servo.
 * 'For' loops are used to increment and decrement the value of 'i'
 ***************************/

//import ax12 library to send DYNAMIXEL commands
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ax12.h>

char d = '';

void setup()
{
    Serial.begin(9600);
    SetPosition(1,512); //set the position of servo # 1 to '0'
    SetPosition(2,512);
    //delay(10);//wait for servo to move
}

void loop()
{
   if (Serial.available() > 0) {
     // Get next command from Serial (add 1 for final 0)
     char c = Serial.read();
     
     if(c == 'n'){
       nod(10, 3, 516, 496);
     } else if(c == 's'){
       shake(10, 3, 528, 496);
     } else if (c == 'c'){
       if(d == 'r'){
         center(10, 528);
       } else {
         center(10, )
       } 
     } else if (c == 'r'){
       d = 'r';
       awaitr(10, 528);
     } else if (c == 'l'){
       d = 'l';
       awaitr(10, 496);

     }
   }
 }
 
// 1 step = 0.35º
int nod(int s, int t, int top, int down){
  for(int i = 513; i < top; i++){
    SetPosition(2, i);
  }
  for(int i = 0; i < t; i++){
    for(int j = top; j > down; j--){
      SetPosition(2, j);
      delay(s);
    }
    for(int j = down; j < top; j++){
      SetPosition(2, j);
      delay(s);
    }
  }
  for(int i = top; i >= 512; i--){
    SetPosition(2, i);
  }
}

int shake(int s, int t, int top, int down){
  for(int i = 0; i < t; i++){
    for(int j = 512; j > down; j--){
      SetPosition(1, j);
      delay(s);
    }
    for(int j = down; j < top; j++){
      SetPosition(1, j);
      delay(s);
    }
  }
  for(int i = top; i >= 512; i--){
    SetPosition(1, i);
  }
}

int awaitr(int s, int top){
  for(int j = 512; j < top; j++){
      SetPosition(1, j);
      delay(s);
    }
}

int awaitl(int s, int top){
  for(int j = 512; j > top; j--){
      SetPosition(1, j);
      delay(s);
    }
}

int center(int s, int from){
  if(from > 512){
    for(int j = from; j >= 512; j--){
      SetPosition(1, j);
      delay(s);
    }
  } else {
    for(int j = from; j <= 512; j++){
      SetPosition(1, j);
      delay(s);
    }
  }
}



