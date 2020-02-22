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

char d = 'a';

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
       nod(20, 3, 526, 486);
     } else if(c == 's'){
       shake(20, 3, 538, 486);
     } else if (c == 'c'){
       if(d == 'r'){
         center(20, 486);
       } else {
         center(20, 538);
       } 
     } else if (c == 'r'){
       d = 'r';
       awayr(20, 486);
       
     } else if (c == 'l'){
       d = 'l';
       awayl(20, 538);
     }
   }
 }
 
// 1 step = 0.35º
int nod(int s, int t, int top, int down){
  for(int i = 513; i < top; i++){
    SetPosition(2, i);
    delay(s);
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
    delay(s);
  }
}

int shake(int s, int t, int top, int down){
  for(int i = 512; i > down; i--){
    SetPosition(1, i);
    delay(s);
  }
  for(int i = 0; i < t; i++){
    for(int j = down; j < top; j++){
      SetPosition(1, j);
      delay(s);
    }
    for(int j = top; j > down; j--){
      SetPosition(1, j);
      delay(s);
    }
  }
  for(int i = down; i <= 512; i++){
    SetPosition(1, i);
    delay(s);
  }
}

int awayl(int s, int top){
  for(int j = 512; j < top; j++){
      SetPosition(1, j);
      delay(s);
    }
}

int awayr(int s, int top){
  for(int j = 512; j > top; j--){
      SetPosition(1, j);
      delay(s);
    }
}

int headup(int s, int top){
  for(int j = 512; j < top; j++){
      SetPosition(2, j);
      delay(s);
    }
}

int headdown(int s, int down){
  for(int j = 512; j > down; j--){
      SetPosition(2, j);
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



