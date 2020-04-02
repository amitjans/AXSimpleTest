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


//Tristeza 1
char panTristeza [SIZE_EMO] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-4,-7,-9,-11,-12,-13,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-12,-10,-6,4,4,6,7,7,7,8,10,11,12,12,12,12,12,13,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,12,13,13,13,12,11,9,6,4,4,2,2,5,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,-4,-4,-5,-5,-5,-6,-6,-7,-8,-9,-9,-9,-9,-10,-10,-10,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-10,-10,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,-32};
char tiltTristeza [SIZE_EMO] = {0,-4,-5,-6,-6,-6,-7,-7,-7,-8,-8,-9,-9,-10,-10,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-10,-8,-7,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,4,6,7,7,8,9,9,10,10,10,10,9,6,3,5,6,7,7,8,9,9,10,11,11,11,11,11,11,11,11,9,8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,58};

//Pensar
char panPensar[SIZE_EMO] = {0,-3,-3,-4,-4,-4,-4,-5,-5,-6,-6,-6,-6,-7,-7,-7,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,4,4,5,5,6,6,7,7,7,7,7,8,8,8,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,8,8,8,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,-4,-5,-5,-6,-6,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-4,-5,-6,-7,-7,-8,-8,-8,-8,-8,8,9,10,10};
char tiltPensar[SIZE_EMO] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,4,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,-5,-5,-6,-6,-6,-7,-7,-7,-7,-7,-8,-8,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-7,-7,-6,-5,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,5,5,5,10,5,5,5,5,5,5,5,5,5,5,5,-5,-5,-5};

int valorPanAnt;

char d = 'a';

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
    if (Serial.available() > 0) {
     // Get next command from Serial (add 1 for final 0)
     char c = Serial.read();
     if(c == 'n'){
       //delay,iterations,center,up,down
       nod(20, 3, 1500, 1514, 1474);
     } else if(c == 's'){
       //delay,iterations,center,left,right
       shake(20, 3, 1500, 11514, 1474);
     } else if (c == 'c'){
       if(d == 'r'){
         center(20, 1, 1474);
       } else if(d == 'l'){
         center(20, 1, 11514);
       } else if(d == 'u'){
         center(20, 2, 11514);
       } else {
         center(20, 2, 1474);
       }
       d = 'c';
     } else if (c == 'r'){
       down_right(20, 1, 1500, 1474);
       d = 'r';
     } else if (c == 'l'){
       up_left(20, 1, 1500, 11514);
       d = 'l';
     } else if (c == 'u'){
       up_left(20, 2, 1500, 11514);
       d = 'u';
     } else if (c == 'd'){
       down_right(20, 2, 1500, 1474);
       d = 'd';
     } else if (c == 'a'){
       anger();
       d = 'd';
     }
   }
  }
}

void movimientoDerecha(){
  int valorPan = 1500;
  int valorTilt = 1500;
  int i;
  for(i=valorPan;i>=1200; i-=10){
    panServo.writeMicroseconds(i);
    delay(30);
  }
  valorPanAnt = i;
}

void movimientoCentro(){
 
 if(valorPanAnt > 1500){
  for(int i=valorPanAnt;i>=1500; i-=10){
    panServo.writeMicroseconds(i);
    delay(30);
  }
 }
 else
  if(valorPanAnt < 1500){
    for(int i=valorPanAnt;i<=1500; i+=10){
      panServo.writeMicroseconds(i);
      delay(30);
    }  
  }
}

void movimientoTristeza(){
  int valorPan = 1500;
  int valorTilt = 1500;
  for(int i=0;i<SIZE_EMO;i++){
    valorPan+=panTristeza[i];
    valorTilt+=tiltTristeza[i];
    panServo.writeMicroseconds(valorPan);   // sets the servo position based on the latest panServo value
    tiltServo.writeMicroseconds(valorTilt); // sets the servo position based on the latest tiltServo value
    delay(25);
  } 
}


void movimientoPensar(){
  int valorPan = 1500;
  int valorTilt = 1500;
  for(int i=0;i<SIZE_EMO;i++){
    valorPan+=panPensar[i];
    valorTilt+=tiltPensar[i];
    panServo.writeMicroseconds(valorPan);   // sets the servo position based on the latest panServo value
    tiltServo.writeMicroseconds(valorTilt); // sets the servo position based on the latest tiltServo value
    delay(20);
  }
  valorPanAnt = valorPan;
}

void movimientoPensar2(){
  int valorPan = 1500;
  int valorTilt = 1500;
  for(int i=0;i<SIZE_EMO;i++){
    panServo.writeMicroseconds(valorPan);   // sets the servo position based on the latest panServo value
    tiltServo.writeMicroseconds(valorTilt); // sets the servo position based on the latest tiltServo value
    delay(20);
  }
  valorPanAnt = valorPan;
}

//***********************************************************************************************************//

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
      if(engine == 1){
        panServo.writeMicroseconds(j);
      } else {
        tiltServo.writeMicroseconds(j)
      }        
      delay(s);
    }
}

int down_right(int s, int engine, int ini, int top){
  for(int j = ini; j > top; j--){
      if(engine == 1){
        panServo.writeMicroseconds(j);
      } else {
        tiltServo.writeMicroseconds(j)
      }
      delay(s);
    }
}

int center(int s, int engine, int from){
  if(from > 1500){
    down_right(s, engine, from, 1499);
  } else {
    up_left(s, engine, from, 1501);
  }
}

int anger(){
  down_right(20, 2, 1500, 1474);
  down_right(20, 1, 1500, 1444);
  shake(20, 3, 1444, 1470, 1418);
  up_left(20, 1, 1444, 1501);
}
