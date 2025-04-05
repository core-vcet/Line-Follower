// Define IR sensor pins
#define IR1 2   // Leftmost sensor
#define IR2 3   // Left-center sensor
#define IR3 4   // Right-center sensor
#define IR4 5   // Rightmost sensor

// Define motor driver control pins
#define LM1 6   // Left motor IN1
#define LM2 7   // Left motor IN2
#define RM1 8   // Right motor IN1
#define RM2 9   // Right motor IN2

// Define PWM pins for motor speed control
#define L_PWM 10  // Left motor speed
#define R_PWM 11  // Right motor speed

// Define base speeds
int speedForward = 150;  // Normal forward speed
int speedTurn = 180;     // Speed for sharp turns or reverse

void setup() {
  // Set IR sensor pins as input
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  // Set motor control pins as output
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  // Set PWM pins as output
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
}

void loop() {
  // Read IR sensor values
  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);

  // Logic based on sensor readings
  if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 0) {
    moveForward(speedForward); // All good, move straight
  } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0) {
    turnSlightRight(); // Slightly off to left, correct right
  } else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 0) {
    turnSharpRight(); // Way off to left, sharp right turn
  } else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1) {
    turnSlightLeft(); // Slightly off to right, correct left
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1) {
    turnSharpLeft(); // Way off to right, sharp left turn
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
    stopMotors(); // All black, stop robot
  } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
    reverse(); // All white, maybe end of path, reverse
  } else {
    moveForward(speedForward); // Default action: move forward
  }
}

// Move forward at given speed
void moveForward(int spd) {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(L_PWM, spd);
  analogWrite(R_PWM, spd);
}

// Move backward
void reverse() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(L_PWM, speedTurn);
  analogWrite(R_PWM, speedTurn);
}

// Stop both motors
void stopMotors() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

// Sharp left turn
void turnSharpLeft() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(L_PWM, speedTurn);
  analogWrite(R_PWM, speedTurn);
}

// Sharp right turn
void turnSharpRight() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(L_PWM, speedTurn);
  analogWrite(R_PWM, speedTurn);
}

// Slight left correction
void turnSlightLeft() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(L_PWM, 100); // Reduce left motor speed
  analogWrite(R_PWM, speedForward);
}

// Slight right correction
void turnSlightRight() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(L_PWM, speedForward);
  analogWrite(R_PWM, 100); // Reduce right motor speed
}
