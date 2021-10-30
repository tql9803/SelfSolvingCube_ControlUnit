// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

// int slaveAddress = 0x80;
// int Register = 0xFB;
// int data = 0x10;

// void setup() {
//   put your setup code here, to run once:
//   Wire.begin();
//   delay(100);
//   Wire.beginTransmission(slaveAddress);
//   Wire.write(Register);
//   Wire.write(data);
//   Wire.endTransmission();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

#include <string.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 

void motorControl(char*instructions);
void motorSelect(int side, char number_of_turns);

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
//char A[] = "U1D1U2D2U3D3L1L2L3R1R2R3F3B3F2B2F1B1"; //Random cube instructions
char A[] = "U1D1L1R1F1B1U2D2L2R2F2B2U3D3L3R3F3B3"; //Random cube instructions

char *Aptr = &A[0];



void setup() {
  //const string b = "cat";
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
  pwm.begin();
  pwm.setPWMFreq(50);  // This is the maximum PWM frequency
 
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
 
}
 
void loop() {
  /*
  // Drive each PWM in a 'wave'
  for (uint16_t i=0; i<4096; i += 8) 
  {
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) 
    {
      pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
      delay(200);
    }
  }
*/
       /*pwm.setPWM(0, 0, 500 );
       delay(5000);
       pwm.setPWM(0, 0, 100 );
       delay(5000);*/
      motorControl(Aptr);
      /*for (int x = 0; x <= 11; x++) 
      {
        delay(50);
        pwm.setPWM(3, 0, (100 + 40*x) );
        pwm.setPWM(0, 0, (100 + 40*x) );

        if (x == 0 || x == 11)
          delay(1000);
      }*/
      //pwm.setPWM(3, 0, 4000 );
}
 

void motorControl (char*instructions)
{
  int side;
  for (int i = 0; i<strlen(instructions); i++)
  {
    if(i % 2 == 0)
    {
      switch(instructions[i]) {
        case 'U' :
          side = 0;
          motorSelect(side, instructions[i+1]);
          break;
        case 'D' :
          side = 1;
          motorSelect(side, instructions[i+1]);
          break;
        case 'L' :
          side = 2;
          motorSelect(side, instructions[i+1]);
          break;
        case 'R' :
          side = 3;
          motorSelect(side, instructions[i+1]);
          break;
        case 'F' :
          side = 4;
          motorSelect(side, instructions[i+1]);
          break;
        case 'B' :
          side = 5;
          motorSelect(side, instructions[i+1]);
          break;
      }
    }
  }
}

void motorSelect(int side, char number_of_turns)
{
  if (number_of_turns == '1')
    pwm.setPWM(side, 0, 500 );
  if (number_of_turns == '2')
    pwm.setPWM(side, 0, 100 );
  if (number_of_turns == '3')
    pwm.setPWM(side, 0, 300 );
  delay(1000);
  
}