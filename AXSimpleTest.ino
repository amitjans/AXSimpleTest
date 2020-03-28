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
       down_right(20, 1, 512, 486);
     } else if (c == 'l'){
       up_left(20, 1, 512, 538);
     } else if (c == 'u'){
       up_left(20, 2, 512, 538);
     } else if (c == 'd'){
       down_right(20, 2, 512, 486);
     } else if (c == 'a'){
       anger();
     }
   }
 }
 
// 1 step = 0.29º
int nod(int s, int t, int ini, int top, int down){
  up_left(s, 2, ini, top);
  for(int i = 0; i < t; i++){
    down_right(s, 2, top, down);
    up_left(s, 2, down, top);
  }
  down_right(s, 2, top, ini);
}

int shake(int s, int t, int ini, int top, int down){
  down_right(s, 1, ini, down);
  for(int i = 0; i < t; i++){
    up_left(s, 1, down, top);  
    down_right(s, 1, top, down);
  }
  up_left(s, 1, down, ini);
}

int up_left(int s, int engine, int ini, int top){
  for(int j = ini; j < top; j++){
      SetPosition(engine, j);
      delay(s);
    }
    d = (engine == 1 ? 'l' : 'u');
}

int down_right(int s, int engine, int ini, int top){
  for(int j = ini; j > top; j--){
      SetPosition(engine, j);
      delay(s);
    }
    d = (engine == 1 ? 'r' : 'd');
}

int center(int s, int engine, int from){
  if(from > 512){
    down_right(s, engine, from, 511);
  } else {
    up_left(s, engine, from, 513);
  }
  d = 'c';
}

int anger(){
  down_right(20, 2, 512, 486);
  down_right(20, 1, 512, 456);
  shake(20, 3, 456, 492, 440);
  up_left(20, 1, 456, 513);
  d = 'd';
}



