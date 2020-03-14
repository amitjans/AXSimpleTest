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
     //n - si
     //s - no
     //c - centrar
     //r - mirar derecha
     //l - mirar izquierda
     //u - arriba
     //d - abajo
     if(c == 'n'){
       //delay,iterations,center,up,down
       nod(20, 3, 512, 526, 486);
     } else if(c == 's'){
       //delay,iterations,center,left,right
       shake(20, 3, 512, 538, 486);
     } else if (c == 'c'){
       if(d == 'r'){
         center(20, 1, 486);
       } else if(d == 'l'){
         center(20, 1, 538);
       } else if(d == 'u'){
         center(20, 2, 538);
       } else {
         center(20, 2, 486);
       }
     } else if (c == 'r'){
       d = 'r';
       awayr(20, 512, 486);
     } else if (c == 'l'){
       d = 'l';
       awayl(20, 512, 538);
     } else if (c == 'u'){
       d = 'u';
       headup(20, 512, 538);
     } else if (c == 'd'){
       d = 'd';
       headdown(20, 512, 486);
     } else if (c == 'a'){
       d = 'd';
       anger();
     }
   }
 }
 
// 1 step = 0.35º
int nod(int s, int t, int ini, int top, int down){
  headup(s, ini, top);
  for(int i = 0; i < t; i++){
    headdown(s, top, down);
    headup(s, down, top);
  }
  headdown(s, top, ini);
}

int shake(int s, int t, int ini, int top, int down){
  awayr(s, ini, down);
  for(int i = 0; i < t; i++){
    awayl(s, down, top);  
    awayr(s, top, down);
  }
  awayl(s, down, ini);
}

int awayl(int s, int ini, int top){
  for(int j = ini; j < top; j++){
      SetPosition(1, j);
      delay(s);
    }
}

int awayr(int s, int ini, int top){
  for(int j = ini; j > top; j--){
      SetPosition(1, j);
      delay(s);
    }
}

int headup(int s, int ini, int top){
  for(int j = ini; j < top; j++){
      SetPosition(2, j);
      delay(s);
    }
}

int headdown(int s, int ini, int down){
  for(int j = ini; j > down; j--){
      SetPosition(2, j);
      delay(s);
    }
}

int center(int s, int engine, int from){
  if(from > 512){
    for(int j = from; j >= 512; j--){
      SetPosition(engine, j);
      delay(s);
    }
  } else {
    for(int j = from; j <= 512; j++){
      SetPosition(engine, j);
      delay(s);
    }
  }
}

int anger(){
  headdown(20, 512, 486);
  awayr(20, 512, 466);
  shake(20, 3, 466, 492, 440);
  awayl(20, 466, 513);
}



