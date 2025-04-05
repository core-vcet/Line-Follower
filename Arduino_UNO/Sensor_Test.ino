int irSensor1 = 2;
int irSensor2 = 3;

void setup() {
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor1State = digitalRead(irSensor1);
  int sensor2State = digitalRead(irSensor2);

  Serial.print("Sensor 1: ");
  Serial.print(sensor1State);
  Serial.print(" | Sensor 2: ");
  Serial.println(sensor2State);

  delay(500);
}
