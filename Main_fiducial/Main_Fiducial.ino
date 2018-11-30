const byte ledPin = 13;
const byte intPin = 2;
const byte crossCheck = 4;
const byte intPin2 = 3
  // Can any interrupt pin be used?
volatile byte state = HIGH;
volatile int tape_num = 0;
volatile int zone = 0;
int t = 0;
int tElapsed = 0;
int tAllowed = 10;
volatile int tape_num2 = 0;

void setup() {
  Serial.begin(9600);
  //pinMode(ledPin, OUTPUT);
  pinMode(intPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(intPin), met_tape, RISING);
//  attachInterrupt(digitalPinToInterrupt(intPin2), met_tape2, RISING);
 // attachInterrupt(digitalPinToInterrupt(encoder, countClicks, RISING));
}

void loop() {

  digitalWrite(ledPin, state);
  if (tape_num1 - tape_num2 >= 2)
  {
    digitalWrite(4, HIGH);
    delay(1);
    digitalWrite(4, LOW);
  }

    
  
//  if tape_num > 1
//  if ( tape_num % 10 == 0 ) {
//    Serial.println(++zone);
//    Serial.println("zone increased");  
//  }
}

void serialEvent () {
  if (Serial.available > 0) { 
       incomingByte = Serial.read();

    // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }
}


void countClicks() {
  clicks++;

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
