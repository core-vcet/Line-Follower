int irSensor1 = 2;
int irSensor2 = 3;
int motorPin = 9;

void setup() {
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int s1 = digitalRead(irSensor1);
  int s2 = digitalRead(irSensor2);

  Serial.print("S1: ");
  Serial.print(s1);
  Serial.print(" | S2: ");
  Serial.println(s2);

  if (s1 == LOW || s2 == LOW) {
    digitalWrite(motorPin, HIGH);  // Turn ON motor
  } else {
    digitalWrite(motorPin, LOW);   // Turn OFF motor
  }

  delay(200);
}
