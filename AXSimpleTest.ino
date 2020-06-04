//Includes
#include <Servo.h>

//Defines
#define PAN_PIN 10        //Pan Servo Digital Pin
#define TILT_PIN 11       //Tilt Servo Digital Pin

#define H_JOY_PIN 0       //Horizontal Joystick Analog Pin
#define V_JOY_PIN 1       //Vertical Joystick Analog Pin

#define LASER_PIN 2       //Laser Digital Pin

#define PUSHBUTTON_PIN 4  //Pushbutton Digital Pin

//deadband values for the joysticks - values between DEADBANDLOW and DEADBANDHIGH will be ignored
#define DEADBANDLOW 480   //lower deadband value for the joysticks  
#define DEADBANDHIGH 540  //upper deadband value for the joysticks  

//max/min puse values in microseconds to send to the servo
#define PAN_MIN      600  //full counterclockwise for RobotGeek 180 degree servo
#define PAN_MAX      2400 //full clockwise for RobotGeek 180 degree servo
#define TILT_MIN  600     //full counterclockwise for RobotGeek 180 degree servo
#define TILT_MAX  2400    //full clockwise for RobotGeek 180 degree servo
#define SIZE_EMO  300
#define SIZE_EMO2  100
int speed = 40;        //alter this value to change the speed of the system. Higher values mean higher speeds 5-500 approximate recommended range

Servo panServo, tiltServo;  // create servo objects to control the pan and tilt servos

int horizontalValue, verticalValue;            //variables to hold the last reading from the analog pins for the horizontal and vertical joystick
int horizontalValueMapped, verticalValueMapped;//variables to hold mapped readings from the vertical values. These mapped readings will be appropriate to work with servo values

int panValue = 1500;   //current positional value being sent to the pan servo.
int tiltValue = 1500;  //current positional value being sent to the tilt servo.

//State Variables
int laserState = LOW;         //The current state of the laser module
int buttonState;             // the current state of the pushbuton
int lastButtonState = LOW;   // the previous reading from the input pin

//Timing variables for button debouncing
long lastDebounceTime = 0;  // the last time the output pin was toggled. This variable is a 'long' because it may need to hold many milliseconds, and a 'long' will afford more space than an 'int'
int debounceDelay = 50;    // the amount of time that that a button must be held, for a reading to register (in milliseconds)

//int panTristeza [SIZE_EMO];
//int tiltTristeza [SIZE_EMO];
int index = 0;
int panBefore = 0;
int tiltBefore = 0;

int valorPanAnt;

char d = 'a';
int s = 10;
int engine1 = 1500;
int engine2 = 1500;

void setup()
{

  Serial.begin(9600);
 
  //initialize servos
  panServo.attach(PAN_PIN, PAN_MIN, PAN_MAX);  // attaches/activates the pan servo on pin PAN_PIN and sets lower/upper limits that can be sent to the servo
  tiltServo.attach(TILT_PIN, TILT_MIN, TILT_MAX);  // attaches/activates the tilt servo on pin TILT_PIN and sets lower/upper limits that can be sent to the servo

  //initalize digital pins
  pinMode(PUSHBUTTON_PIN, INPUT);  //set the PUSHBUTTON Pin to an Input
  pinMode(LASER_PIN, OUTPUT);      //set the LASER Pin to an output
  
  //write initial servo positions to set the servos to 'home'
  panServo.writeMicroseconds(panValue);  //sets the pan servo position to the default 'home' value
  tiltServo.writeMicroseconds(tiltValue);//sets the tilt servo position to the default 'home' value
 
}


void loop(){
  if(Serial.available()>0){
     char c = Serial.read();
     if(c == 'n' || c == 'N'){
       //delay,iterations,center,up,down
       nod(3, (c == 'N' ? 1600 : ((1500 + 1600) / 2)), (c == 'N' ? 1300 : ((1500 + 1300) / 2)));
     } else if(c == 's' || c == 'S'){
       //delay,iterations,center,left,right
       shake(3, (c == 'S' ? 1700 : ((1500 + 1700) / 2)), (c == 'S' ? 1300 : ((1500 + 1300) / 2)));
     } else if (c == 'c'){
       center();
       d = 'c';
     } else if (c == 'r' || c == 'R'){
       engine1 = down_right(1, c == 'R' ? 1300 : ((1500 + 1300) / 2));
       d = 'r';
     } else if (c == 'l' || c == 'L'){
       engine1 = up_left(1, c == 'L' ? 1700 : ((1500 + 1700) / 2));
       d = 'l';
     } else if (c == 'u' || c == 'U'){
       engine2 = up_left(2, c == 'U' ? 1700 : ((1500 + 1700) / 2));
       d = 'u';
     } else if (c == 'd' || c == 'D'){
       engine2 = down_right(2, c == 'D' ? 1300 : ((1500 + 1300) / 2));
       d = 'd';
     } else if (c == 'a'){
       anger();
       d = 'd';
     }
   }
   }

//***********************************************************************************************************//

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
  while(engine1 != 1500 || engine2 != 1500){
    if(engine1 != 1500){
      if(engine1 > 1500){ engine1--; } else { engine1++; }
      SetPosition(1, engine1);
    }
    if(engine2 != 1500){
      if(engine2 > 1500){ engine2--; } else { engine2++; }
      SetPosition(2, engine2);
    }
    delay(s);
  }
}

void anger(){
  engine2 = down_right(2, 1300);
  engine1 = down_right(1, 1220);
  shake(3, 1316, 1176);
  engine1 = up_left(1, 1500);
}

void SetPosition(int engine, int pos){
  if(engine == 1){
    panServo.writeMicroseconds(pos);
  } else {
    tiltServo.writeMicroseconds(pos);
  }
}
