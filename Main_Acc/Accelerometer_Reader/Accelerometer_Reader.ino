#include<Wire.h>

#define XYZ_DATA 0x32
#define POWER_CTL 0x2D
#define ACCE_ADDR 0x53
#define FIFO_CTL 0x38
#define DATA_FORMAT 0x31
#define THRESH_ACT 0x24
#define INT_ENABLE 0x2E
#define INT_MAP 0x2F
#define ACT_INACT_CTL 0x27

byte values[6];
char output[512];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
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
}

void loop() {
  // put your main code here, to run repeatedly:
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
  
  Serial.println();
}
