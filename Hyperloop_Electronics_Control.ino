#include<Wire.h>

#include<Encoder.h>

#define XYZ_DATA 0x32

#define POWER_CTL 0x2D

#define ACCE_ADDR 0x53

#define FIFO_CTL 0x38

#define DATA_FORMAT 0x31

#define THRESH_ACT 0x24

#define INT_ENABLE 0x2E

#define INT_MAP 0x2F

#define ACT_INACT_CTL 0x27


//wheel diameter in inches
const int wheelDia = 16;
//ratio of wheel turns to motor turns
const float wheelTurnsPerMotorTurn = 0.88;
//this number depends on the amount of marks per rotation of the encoder
//one mark is 2 pulses on either output, this can be determined experimentally
const int encMarks = 6;
long posTotal;
byte values[6];

char output[512];
const byte crossCheck = 4;
const byte state = LOW;
//int t = 0;
//int tElapsed = 0;
//int tAllowed = 10;
volatile byte incomingByte = 0;
int tape_num1 = 0;
volatile byte incomingByte2 = 0;
int tape_num2 = 0;
const byte restartByte = 0x55;
const byte restartByte2 = 0x55;
int brakePin = 5;
int checkPin = 13;
int lastPulse = 0;
int threshold = 5000;
int encDist; 
int fidDist;
//these should both be interrupt pins
Encoder enc(2, 3);

void setup() {
  float k = (wheelTurnsPerMotorTurn * wheelDia) / (4*encMarks);
  pinMode(brakePin, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  delay(100);
  //pinMode(ledPin, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(encoder, countClicks, RISING);

  Wire.begin();

  //Set to measurement mode

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(POWER_CTL);

  Wire.write(8);

  Wire.endTransmission();

  //Set to stream mode

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(FIFO_CTL);

  Wire.write(0b10011111);

  Wire.endTransmission();  



  //Set to 4g full resolution

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(DATA_FORMAT);

  Wire.write(0b00001011);

  Wire.endTransmission();



  //Set threshold for actibity interrupt

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(THRESH_ACT);

  Wire.write((byte)(2.0/(0.015625))); //2 g

  Wire.endTransmission();



  //choose y, z axis for measurement against threshold

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(ACT_INACT_CTL);

  Wire.write(0b00110000);

  Wire.endTransmission();



  //send all data to interrupt 1

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(INT_MAP);

  Wire.write(0b00000000);

  Wire.endTransmission();



  //Enable activity interrupt

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(INT_ENABLE);

  Wire.write(0b00010000);

  Wire.endTransmission();

  delay(1000);



  Serial2.write(restartByte);
  Serial3.write(restartByte);
  delay(10);

}

void loop() {
  posTotal = enc.read();
  encDist = posTotal * k;

  
 
  digitalWrite(checkPin, HIGH);

   int x, y, z;

  Wire.beginTransmission(ACCE_ADDR);

  Wire.write(XYZ_DATA);

  Wire.endTransmission();



  Wire.requestFrom(ACCE_ADDR, 6);



  int i = 0;

  while(Wire.available())    // slave may send less than requested

  { 

    values[i] = Wire.read();

    i++;

  } 



  x = (((int)values[1]) << 8) | values[0];

  y = (((int)values[3]) << 8) | values[2];

  z = (((int)values[5]) << 8) | values[4];

  
  
  sprintf(output, "%d %d %d", x, y, z);

  Serial.print(output);
  communicate_with_rasp(x, y, z);



  

  Serial.println();

//  if (tape_num2 - tape_num1 >= 2)
//  {
//    digitalWrite(brakePin, HIGH);
//    
//  }

  checkFids(incomingByte,incomingByte2, encDist);

    
}


void serialEvent2() {
  if (Serial2.available() > 0) { 
       incomingByte2 = Serial2.read();
       
    // say what you got:
      Serial.print("I received fid back: ");
      Serial.println(incomingByte2, DEC);
      
    }
    checkFids(incomingByte,incomingByte2, encDist);
  
    
}

void serialEvent3() {
  if (Serial3.available() > 0) { 
       incomingByte = Serial3.read();
       
    // say what you got:
      Serial.print("I received fid front: ");
      Serial.println(incomingByte, DEC);
    }
    checkFids(incomingByte,incomingByte2);
}

void checkFids(int x, int y, int z) {
  int now = millis();
  //the fidutial distance in 
  fidDist = x * 100;
  if(abs(x - y) > 1 || abs(fidDist - z) == 100 || now - lastPulse > threshold)
      {
        //activate E-stop condition
        digitalWrite(checkPin, LOW);
        delay(50);
      }
  lastPulse = millis();
}

void communicate_with_rasp(int x, int y, int z) {
  String delim = ",";
  Serial1.print(x + delim + y + delim + z + delim + incomingByte + delim + incomingByte2+"\n");
}
