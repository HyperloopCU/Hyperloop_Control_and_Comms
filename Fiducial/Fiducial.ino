const byte intPin = 3;
volatile int tape_num;


void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(intPin), fidCount, RISING);
  
  // put your setup code here, to run once:
//
}

void loop() {
  // put your main code here, to run repeatedly:

}

void fidCount() {
  tape_num++;
  Serial.write(tape_num);
  Serial.println(tape_num);
}
