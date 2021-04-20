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
     if (c == 'c'){
       center();
       d = 'c';
     } else if (c == 'r' || c == 'R'){
       engine1 = down_right(1, c == 'R' ? 26 : 13);
       d = 'r';
     } else if (c == 'l' || c == 'L'){
       engine1 = up_left(1, c == 'L' ? 26 : 13);
       d = 'l';
     } else if (c == 'u' || c == 'U'){
       engine2 = up_left(2, c == 'U' ? 26 : 13);
       d = 'u';
     } else if (c == 'd' || c == 'D'){
       engine2 = down_right(2, c == 'D' ? 26 : 13);
       d = 'd';
     } else if ( c == 'h') {
       String codes = "[{\"code\":\"c\",\"symbol\":\"&olarr;\"},";
       codes = codes + "{\"code\":\"r\",\"symbol\":\"&rarr;\"},";
       codes = codes + "{\"code\":\"l\",\"symbol\":\"&larr;\"},";
       codes = codes + "{\"code\":\"u\",\"symbol\":\"&uarr;\"},";
       codes = codes + "{\"code\":\"d\",\"symbol\":\"&darr;\"},";
       codes = codes + "{\"code\":\"R\",\"symbol\":\"&rrarr;\"},";
       codes = codes + "{\"code\":\"L\",\"symbol\":\"&llarr;\"},";
       codes = codes + "{\"code\":\"U\",\"symbol\":\"&uuarr;\"},";
       codes = codes + "{\"code\":\"D\",\"symbol\":\"&ddarr;\"}]";
       Serial.println(codes);
     } else {
       onestep(c);
     }
   }
 }
 
// 1 step = 0.29º
int up_left(int engine, int top){
  int j = (engine == 1 ? engine1 : engine2);
  top = top + j;
  while(j != top){
    j++;
    SetPosition(engine, j);
    delay(s);
  }
  return j;
}

int down_right(int engine, int top){
  int j = (engine == 1 ? engine1 : engine2);
  top = j - top;
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
