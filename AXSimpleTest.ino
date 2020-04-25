//import ax12 library to send DYNAMIXEL commands
#include <ax12.h>

char d = 'a';
int s = 20;
int engine1 = 512;
int engine2 = 512;

void setup()
{
    Serial.begin(9600);
    SetPosition(1,engine1);
    SetPosition(2,engine2);
}

void loop()
{
   if (Serial.available() > 0) {
     // Get next command from Serial (add 1 for final 0)
     char c = Serial.read();
     if(c == 'n'){
       //iterations,up,down
       nod(3, 526, 486);
     } else if(c == 's'){
       //iterations,left,right
       shake(3, 538, 486);
     } else if (c == 'c'){
       center();
       d = 'c';
     } else if (c == 'r'){
       engine1 = down_right(1, 486);
       d = 'r';
     } else if (c == 'l'){
       engine1 = up_left(1, 538);
       d = 'l';
     } else if (c == 'u'){
       engine2 = up_left(2, 538);
       d = 'u';
     } else if (c == 'd'){
       engine2 = down_right(2, 486);
       d = 'd';
     } else if (c == 'a'){
       anger();
       d = 'd';
     }
   }
 }
 
// 1 step = 0.29º
int nod(int t, int top, int down){
  int temp = engine2;
  engine2 = up_left(2, top);
  for(int i = 0; i < t; i++){
    engine2 = down_right(2, down);
    engine2 = up_left(2, top);
  }
  engine2 = down_right(2, temp);
}

int shake(int t, int top, int down){
  int temp = engine2;
  engine1 = down_right(1, down);
  for(int i = 0; i < t; i++){
    engine1 = up_left(1, top);  
    engine1 = down_right(1, down);
  }
  engine1 = up_left(1, temp);
}

int up_left(int engine, int top){
  int j = (engine == 1 ? engine1 : engine2);
  while(j != top){
    j++;
    SetPosition(engine, j);
    delay(s);
  }
  return j;
}

int down_right(int engine, int top){
  int j = (engine == 1 ? engine1 : engine2);
  while(j != top){
    j--;
    SetPosition(engine, j);
    delay(s);
  }
  return j;
}

void center(){
  while(engine1 != 512 || engine2 != 512){
    if(engine1 != 512){
      if(engine1 > 512){ engine1--; } else { engine1++; }
      SetPosition(1, engine1);
    }
    if(engine2 != 512){
      if(engine2 > 512){ engine2--; } else { engine2++; }
      SetPosition(2, engine2);
    }
    delay(s);
  }
}

int anger(){
  engine2 = down_right(2, 486);
  engine1 = down_right(1, 456);
  shake(3, 492, 440);
  engine1 = up_left(1, 512);
}



