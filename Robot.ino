#include <Servo.h>
#include <NewPing.h> 
#include <Talkie.h>

const int LeftMotorForward = 5;
const int LeftMotorBackward = 4;
const int RightMotorForward = 2;
const int RightMotorBackward = 3;

#define trig_pin A1
#define echo_pin A2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance);
Servo servo_motor;
Talkie voice;

/* Directions */
const int8_t spDOWN[]      PROGMEM = {0x08,0x48,0x60,0x82,0xD4,0x8E,0xBA,0x57,0xB4,0xED,0xE6,0x74,0x92,0x6A,0x1E,0x8D,0x4F,0xD4,0x54,0x6A,0x8A,0xB7,0x3A,0x51,0x13,0x2B,0xA5,0xB1,0xE8,0x44,0x55,0x9F,0x95,0x58,0xAB,0x13,0x55,0xFB,0x9E,0xEA,0xAD,0x4E,0x5C,0xED,0x47,0xA9,0x37,0x3C,0x69,0x35,0x1F,0x69,0xD1,0xF0,0xE4,0xD5,0x5D,0xA4,0xF9,0xAA,0x53,0x96,0xB0,0x51,0x66,0x8B,0x4E,0x5D,0xDC,0x7A,0x86,0xAE,0x1C,0x43,0x29,0x6D,0x29,0x76,0x2B,0x8D,0x29,0xA4,0x78,0xE4,0xAC,0x30,0xC5,0xEC,0xE2,0x51,0x93,0xDC,0x14,0x93,0xAB,0xD8,0x34,0x72,0x53,0x32,0x96,0xA2,0x99,0xD9,0x8D,0x49,0xC8,0xB8,0x86,0x67,0x33,0x44,0x21,0x53,0x16,0x5A,0xCC,0xE0,0x65,0x54,0x69,0xBA,0x36,0x7D,0xE4,0xDA,0xA5,0xA3,0xF8,0xFF,0x51};
const int8_t spUP[]        PROGMEM = {0x27,0xAA,0x66,0x33,0x5D,0x16,0x9E,0xB0,0xDA,0xCB,0x32,0x9D,0x79,0xA2,0x2A,0x2F,0x23,0xB4,0xE5,0x49,0xBA,0xB8,0xCE,0xE2,0xCE,0xA7,0x6A,0x72,0xBB,0x9A,0xBA,0x94,0x36,0x87,0xCE,0x66,0x59,0x45,0x26,0xA1,0xDC,0x5D,0x44,0x36,0x00,0x00,0x03,0xBC,0x4F,0x13,0x40,0x52,0xA1,0xFF,0x35};
const int8_t spRIGHT[]     PROGMEM = {
  0x66,0xD7,0xB1,0x24,0xDC,0xE3,0x98,0xCD,0x95,0xA4,0x28,0xB5,0x97,0xD6,0xD0,0x8C,0x3A,0x55,0xFE,0x18,0x43,0xB1,0x4C,0x37,0x6F,0xA7,0x2D,0x72,0x22,0x8A,0xF3,0x9E,
  0xA6,0xFA,0x94,0x0A,0xDD,0x7C,0x9B,0xDB,0xAD,0xB1,0xD7,0x40,0xF3,0x78,0x3D,0xE7,0x7E,0xE6,0x07,0x81,0x22,0x94,0xBB,0x88,0x6C,0x00,0x50,0xC0,0xB6,0xD7,0x1E,0x10,
  0x40,0x9B,0xEB,0x0C,0x28,0x56,0xE9,0xFF,0x01};
  
const int8_t spLEFT[]      PROGMEM = {0x69,0x1D,0xC0,0xDA,0xCC,0xD3,0xA6,0xB5,0x81,0x68,0xD1,0xF4,0xDA,0xC7,0xD3,0x57,0x6F,0x11,0xDC,0x4B,0x6E,0x73,0x9A,0xE6,0x5D,0x5B,0x72,0xF5,0xED,0xF7,0xD2,0xCE,0x92,0x2C,0x5C,0xEA,0x0D,0x03,0x8A,0x0E,0x25,0xC0,0x74,0xE3,0x12,0xD0,0x80,0x04,0x10,0x90,0x89,0x2B,0x08,0x60,0x8B,0x71,0x0B,0x10,0xA0,0xB5,0xF3,0xFF,0x07};

/* Greetings */
const int8_t spGOOD[]      PROGMEM = {0x0A,0x28,0xCD,0x34,0x20,0xD9,0x1A,0x45,0x74,0xE4,0x66,0x24,0xAD,0xBA,0xB1,0x8C,0x9B,0x91,0xA5,0x64,0xE6,0x98,0x21,0x16,0x0B,0x96,0x9B,0x4C,0xE5,0xFF,0x01};
const int8_t spMORNING[]   PROGMEM = {0xCE,0x08,0x52,0x2A,0x35,0x5D,0x39,0x53,0x29,0x5B,0xB7,0x0A,0x15,0x0C,0xEE,0x2A,0x42,0x56,0x66,0xD2,0x55,0x2E,0x37,0x2F,0xD9,0x45,0xB3,0xD3,0xC5,0xCA,0x6D,0x27,0xD5,0xEE,0x50,0xF5,0x50,0x94,0x14,0x77,0x2D,0xD8,0x5D,0x49,0x92,0xFD,0xB1,0x64,0x2F,0xA9,0x49,0x0C,0x93,0x4B,0xAD,0x19,0x17,0x3E,0x66,0x1E,0xF1,0xA2,0x5B,0x84,0xE2,0x29,0x8F,0x8B,0x72,0x10,0xB5,0xB1,0x2E,0x4B,0xD4,0x45,0x89,0x4A,0xEC,0x5C,0x95,0x14,0x2B,0x8A,0x9C,0x34,0x52,0x5D,0xBC,0xCC,0xB5,0x3B,0x49,0x69,0x89,0x87,0xC1,0x98,0x56,0x3A,0x21,0x2B,0x82,0x67,0xCC,0x5C,0x85,0xB5,0x4A,0x8A,0xF6,0x64,0xA9,0x96,0xC4,0x69,0x3C,0x52,0x81,0x58,0x1C,0x97,0xF6,0x0E,0x1B,0xCC,0x0D,0x42,0x32,0xAA,0x65,0x12,0x67,0xD4,0x6A,0x61,0x52,0xFC,0xFF};
const int8_t spAFTERNOON[] PROGMEM = {0xC7,0xCE,0xCE,0x3A,0xCB,0x58,0x1F,0x3B,0x07,0x9D,0x28,0x71,0xB4,0xAC,0x9C,0x74,0x5A,0x42,0x55,0x33,0xB2,0x93,0x0A,0x09,0xD4,0xC5,0x9A,0xD6,0x44,0x45,0xE3,0x38,0x60,0x9A,0x32,0x05,0xF4,0x18,0x01,0x09,0xD8,0xA9,0xC2,0x00,0x5E,0xCA,0x24,0xD5,0x5B,0x9D,0x4A,0x95,0xEA,0x34,0xEE,0x63,0x92,0x5C,0x4D,0xD0,0xA4,0xEE,0x58,0x0C,0xB9,0x4D,0xCD,0x42,0xA2,0x3A,0x24,0x37,0x25,0x8A,0xA8,0x8E,0xA0,0x53,0xE4,0x28,0x23,0x26,0x13,0x72,0x91,0xA2,0x76,0xBB,0x72,0x38,0x45,0x0A,0x46,0x63,0xCA,0x69,0x27,0x39,0x58,0xB1,0x8D,0x60,0x1C,0x34,0x1B,0x34,0xC3,0x55,0x8E,0x73,0x45,0x2D,0x4F,0x4A,0x3A,0x26,0x10,0xA1,0xCA,0x2D,0xE9,0x98,0x24,0x0A,0x1E,0x6D,0x97,0x29,0xD2,0xCC,0x71,0xA2,0xDC,0x86,0xC8,0x12,0xA7,0x8E,0x08,0x85,0x22,0x8D,0x9C,0x43,0xA7,0x12,0xB2,0x2E,0x50,0x09,0xEF,0x51,0xC5,0xBA,0x28,0x58,0xAD,0xDB,0xE1,0xFF,0x03};
const int8_t spEVENING[]   PROGMEM = {0xCD,0x6D,0x98,0x73,0x47,0x65,0x0D,0x6D,0x10,0xB2,0x5D,0x93,0x35,0x94,0xC1,0xD0,0x76,0x4D,0x66,0x93,0xA7,0x04,0xBD,0x71,0xD9,0x45,0xAE,0x92,0xD5,0xAC,0x53,0x07,0x6D,0xA5,0x76,0x63,0x51,0x92,0xD4,0xA1,0x83,0xD4,0xCB,0xB2,0x51,0x88,0xCD,0xF5,0x50,0x45,0xCE,0xA2,0x2E,0x27,0x28,0x54,0x15,0x37,0x0A,0xCF,0x75,0x61,0x5D,0xA2,0xC4,0xB5,0xC7,0x44,0x55,0x8A,0x0B,0xA3,0x6E,0x17,0x95,0x21,0xA9,0x0C,0x37,0xCD,0x15,0xBA,0xD4,0x2B,0x6F,0xB3,0x54,0xE4,0xD2,0xC8,0x64,0xBC,0x4C,0x91,0x49,0x12,0xE7,0xB2,0xB1,0xD0,0x22,0x0D,0x9C,0xDD,0xAB,0x62,0xA9,0x38,0x53,0x11,0xA9,0x74,0x2C,0xD2,0xCA,0x59,0x34,0xA3,0xE5,0xFF,0x03};
const int8_t spGOODBYE[]   PROGMEM = {0xA9,0x49,0xE1,0x54,0x91,0x2D,0xAF,0x22,0x07,0x55,0x29,0x69,0x7B,0xF2,0x18,0x38,0x32,0x3C,0xCB,0x4D,0x52,0xC8,0x4A,0x5A,0x65,0x99,0x52,0x21,0x6A,0x61,0x69,0x2E,0x45,0x46,0x2C,0x43,0xA9,0x3C,0x3D,0x1C,0x87,0x2A,0x3A,0xFB,0x50,0x6E,0x73,0xEB,0xDB,0xEC,0x6E,0x77,0xA3,0xF7,0xD1,0x4E,0x35,0xA2,0xCC,0x7E,0x74,0x3E,0xC6,0xA8,0x79,0x85,0xD1,0x86,0x64,0x65,0x16,0x95,0x5B,0x13,0x52,0xB0,0x65,0x94,0x2E,0xB5,0x4D,0x6A,0x55,0x65,0xF8,0x01,0x00,0x00};

/* Others */
const int8_t spWALL[]      PROGMEM = {0x28,0x87,0x6b,0x8d,0xd4,0x95,0x92,0x1c,0x8f,0x0d,0xd0,0x70,0xa3,0x08,0x56,0x6e,0x48,0x5c,0x89,0xc3,0xa5,0xdf,0x65,0x74,0x27,0x01,0xd3,0x71,0x97,0x30,0x93,0x24,0xcc,0x85,0x59,0xa2,0x6c,0x5d,0x30,0x1f,0x67,0x88,0xb3,0x71,0x11,0xa2,0xd9,0x21,0x8e,0xd9,0x25,0x4f,0xe6,0x96,0x28,0x26,0xa7,0x36,0xe9,0x5b,0xc6,0xb8,0x1c,0x82,0x68,0x6f,0x88,0x6b,0x74,0x88,0xa3,0xfd,0x61,0xcc,0x51,0x2e,0x8f,0xe6,0x87,0xa9,0x4e,0xb9,0x36,0xea,0x5f,0xc6,0x3c,0x65,0xe6,0xa8,0x7f,0x90,0x72,0x32,0x6b,0x7d,0x7a,0x87,0xec,0xd2,0x24,0x70,0xfb,0x08,0xb3,0x43,0xa3,0xc0,0xde,0x46,0xee,0x16,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x0f};
const int8_t spON[]        PROGMEM = {0x65, 0x4A, 0xEA, 0x3A, 0x5C, 0xB2, 0xCE, 0x6E, 0x57, 0xA7, 0x48, 0xE6, 0xD2, 0x5D, 0xBB, 0xEC, 0x62, 0x17, 0xBB, 0xDE, 0x7D, 0x9F, 0xDA, 0x5C, 0x5C, 0x7A, 0xAA, 0xB5, 0x6E, 0xCB, 0xD0, 0x0E, 0xAD, 0x6E, 0xAF, 0xEE, 0xF9, 0x88, 0x67, 0xBC, 0xDC, 0x3D, 0xAC, 0x60, 0xB8, 0x45, 0xF3, 0xB7, 0xBF, 0xC3, 0xDD, 0xA2, 0xBB, 0xAB, 0xCD, 0x89, 0x8F, 0x7F, 0xFE, 0x1F};
const int8_t spOFF[]       PROGMEM = {0xCD,0xCB,0x7E,0x52,0x55,0x1A,0xAD,0x28,0xFB,0x2B,0x33,0xCD,0x74,0x83,0x13,0x66,0xF7,0xA5,0x6A,0xAD,0x56,0x5C,0xF4,0x4E,0x38,0x75,0x6E,0x79,0x0A,0x5B,0xA6,0xF2,0x28,0xB5,0xA1,0x8E,0x9B,0xC5,0xEC,0xD0,0x27,0x97,0x19,0x6A,0x8D,0x14,0x50,0x6C,0x87,0x00,0x9A,0x6D,0x67,0xC0,0x34,0xE9,0x04,0x98,0xA6,0x82,0x00,0xCD,0x55,0x10,0xA0,0x9B,0x70,0x04,0x54,0x53,0xFE,0x11,0x19,0x79};
const int8_t spSORRY[]     PROGMEM = {0x06,0x38,0xD6,0xD4,0x03,0x01,0xF8,0x5E,0x35,0x00,0x3F,0xBA,0x45,0x20,0x03,0xCB,0x77,0xD6,0xDA,0x35,0x6D,0x9F,0xD8,0x27,0xDF,0x10,0x4F,0x7B,0xE3,0x13,0x87,0x6C,0xE7,0xA6,0x69,0x6E,0x7C,0x12,0x57,0xEC,0xCC,0xB5,0xED,0xCA,0x4C,0xB3,0xB3,0x94,0x2C,0xA3,0xB2,0x4D,0xC7,0x06,0xD7,0x8E,0xC6,0x57,0x69,0x19,0x69,0x37,0xFB,0xD1,0xA7,0xCA,0x66,0x31,0x0D,0x7B,0xDF,0xFA,0x32,0xC8,0x35,0x36,0x56,0xE9,0x72,0x03,0xB3,0x38,0x49,0xA5,0xAD,0xD5,0x21,0xB4,0x4B,0x9B,0xC6,0x19,0xE6,0xF7,0x90,0xF2};
const int8_t spRUNNING[]   PROGMEM = {0x22,0x11,0xAE,0x5C,0xA3,0x94,0x98,0x4A,0xB8,0x0E,0xF7,0x92,0x67,0x2A,0x1E,0xDB,0x4D,0x5B,0xA9,0x29,0x78,0x49,0xD3,0x0C,0x27,0x21,0x37,0x49,0xCD,0xBB,0xD8,0x8E,0x38,0x35,0x71,0x2D,0xF7,0x70,0xA2,0x92,0xB3,0xCC,0x35,0xD5,0x89,0x6A,0xD8,0x0C,0x8D,0x94,0x27,0x6C,0x7E,0x32,0x38,0x5D,0xAE,0xB0,0x7B,0x0F,0xC5,0xF6,0xD8,0xA2,0xCA,0x4D,0x9A,0x5B,0x75,0x49,0x0B,0x75,0x59,0x2A,0xB5,0x2B,0x99,0xCE,0xD1,0x7D,0x22,0x8F,0x7A,0x78,0x25,0xCF,0xA9,0x3C,0xBA,0x15,0x1A,0xA5,0xAA,0x52,0x1A,0x66,0x12,0xE8,0xAE,0xD0,0x7A,0x52,0x53,0x96,0x1A,0x45,0xD6,0x54,0x4D,0x49,0x6A,0x1A,0x79,0x56,0x35,0x66,0xC5,0xE5,0xE4,0x59,0xD4,0x10,0x95,0x95,0x6A,0x64,0xD6,0x83,0x1D,0x5C,0x5F,0x9C,0x4B,0x88,0xD9,0xF1,0x03,0x02,0x9C,0x51,0xFD,0x65};
const int8_t spSTOP[]     PROGMEM = {0x08,0xF8,0x92,0x8D,0x00,0x5F,0x89,0x32,0xE0,0x6B,0x35,0x01,0x7C,0xAD,0x2A,0x80,0xEF,0x55,0x04,0xF0,0xA3,0x08,0x01,0xBE,0x13,0x46,0xA0,0x50,0xEE,0x2E,0x22,0x1B,0x1C,0xB0,0x8D,0xD5,0x70,0x9B,0xCE,0x10,0xB3,0x4E,0x27,0xCC,0xB1,0x3D,0x59,0x33,0x9F,0x38,0xC7,0xA9,0x74,0xD3,0x7D,0xB3,0x51,0xA4,0x58,0x9D,0xC9,0xB9,0x51,0x23,0x94,0xBB,0x8B,0xC8,0x06,0x00,0x60,0x80,0x57,0x96,0x04,0xC8,0xCE,0x1D,0x01,0x79,0x84,0x22,0xC0,0x3B,0xF7,0xFF,0x09,0x61,0x15,0x49,0x75,0x65};

void setup(){
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(11);

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
  distance = readPing();
}

int lookRight(){
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){

  //voice.say(spSTOP);
  //servo_motor.write(90);
  //voice.say(spSORRY);
  //servo_motor.write(90);
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

  

void moveForward(){
  if(!goesForward){
    goesForward=true;
    //voice.say(spRUNNING);
    //servo_motor.write(90);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){
  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  // voice.say(spRIGHT);
  //servo_motor.write(90);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnLeft(){

  //voice.say(spLEFT);
  //servo_motor.write(90);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
