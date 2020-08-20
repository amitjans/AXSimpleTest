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
     if(c == 'n' || c == 'N'){
       //iterations,up,down
       nod(3, (c == 'N' ? 526 : ((512 + 526) / 2)), (c == 'N' ? 486 : ((512 + 486) / 2)));
     } else if(c == 's' || c == 'S'){
       //iterations,left,right
       shake(3, (c == 'S' ? 538 : ((512 + 538) / 2)), (c == 'S' ? 486 : ((512 + 486) / 2)));
     } else if (c == 'c'){
       center();
       d = 'c';
     } else if (c == 'r' || c == 'R'){
       engine1 = down_right(1, c == 'R' ? 486 : ((512 + 486) / 2));
       d = 'r';
     } else if (c == 'l' || c == 'L'){
       engine1 = up_left(1, c == 'L' ? 538 : ((512 + 538) / 2));
       d = 'l';
     } else if (c == 'u' || c == 'U'){
       engine2 = up_left(2, c == 'U' ? 538 : ((512 + 538) / 2));
       d = 'u';
     } else if (c == 'd' || c == 'D'){
       engine2 = down_right(2, c == 'D' ? 486 : ((512 + 486) / 2));
       d = 'd';
     } else if (c == 'a'){
       anger();
       d = 'd';
     } else {
       onestep(c);
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
  int temp = engine1;
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

void onestep(char c){
  if(c == 't'){
    engine2++;
  } else if(c == 'f'){
    engine1++;
  } else if(c == 'h'){
    engine1--;
  } else if(c == 'g'){
    engine2--;
  }
  SetPosition(1, engine1);
  SetPosition(2, engine2);
}



