byte values[6];

char output[512];

const byte ledPin = 13;
const byte intPin = 2;
const byte crossCheck = 4;
const byte intPin2 = 3;
  // Can any interrupt pin be used?
volatile byte state = LOW;
volatile int tape_num = 0;
volatile int zone = 0;
int t = 0;
int tElapsed = 0;
int tAllowed = 10;
volatile int tape_num2 = 0;
volatile byte incomingByte = 0;
volatile byte incomingByte2 = 0;
const byte restartByte = 0x55;
const byte restartByte2 = 0x55;



void setup() {
  Serial3.begin(9600);
  Serial.begin(9600);
  Serial2.begin(9600);
  //pinMode(ledPin, OUTPUT);
  pinMode(intPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(intPin), met_tape, RISING);
//  attachInterrupt(digitalPinToInterrupt(intPin2), met_tape2, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder, countClicks, RISING);

  Serial2.write(restartByte);
  Serial3.write(restartByte);
}

void loop() {
  digitalWrite(ledPin, HIGH);

//  digitalWrite(ledPin, state);
//  if (tape_num1 - tape_num2 >= 2)
//  {
//    digitalWrite(4, HIGH);
//    delay(1);
//    digitalWrite(4, LOW);
//  }

    
  
//  if tape_num > 1
//  if ( tape_num % 10 == 0 ) {
//    Serial.println(++zone);
//    Serial.println("zone increased");  
//  }
}


void serialEvent2() {
  if (Serial2.available() > 0) { 
       incomingByte2 = Serial2.read();
       
    // say what you got:
      Serial.print("I received fid back: ");
      Serial.println(incomingByte2, DEC);
      tape_num2++;
    }
}

void serialEvent3() {
  if (Serial3.available() > 0) { 
       incomingByte = Serial3.read();
       
    // say what you got:
      Serial.print("I received fid front: ");
      Serial.println(incomingByte, DEC);
      tape_num++;
    }
}


//void countClicks() {
//  clicks++;

//void met_tape() {
//  state = !state;
//  //Serial.println(tape_num);
//  tape_num++;
//  t = millis();
//  }
//}
//
//void met_tape2() {
//  tElapsed = millis() - t;
//  tape_num2++;
//  if (tElapsed > tAllowed)
//  {
//    digitalWrite(4, HIGH);
//    delay(1);
//    digitalWrite(4,  LOW);
//  }
//}
//
