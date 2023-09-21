// Pin definitions
#define speed_motor1 3
#define speed_motor2 5
#define forward_motor1 2
#define backward_motor1 4
#define forward_motor2 6
#define backward_motor2 7



void setup(){
  pinMode(speed_motor1, OUTPUT);
  pinMode(speed_motor2, OUTPUT);
  pinMode(forward_motor1, OUTPUT);
  pinMode(backward_motor1, OUTPUT);
  pinMode(forward_motor2, OUTPUT);
  pinMode(backward_motor2, OUTPUT);

}
void Stop()
{
  digitalWrite(forward_motor1, LOW);
  digitalWrite(backward_motor1, LOW);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(backward_motor2, LOW);
  Serial.println("stop");
}
void forward(int distance) {
  unsigned long startTime = millis();
  while (millis() - startTime < distance) {
    analogWrite(speed_motor1, Speed);
    digitalWrite(forward_motor1, HIGH);
    digitalWrite(backward_motor1, LOW);
    analogWrite(speed_motor2, Speed);
    digitalWrite(forward_motor2, HIGH);
    digitalWrite(backward_motor2, LOW);
    Serial.println("forward");
  }
  Stop();
}

void backward(int distance) {
  unsigned long startTime = millis();
  while (millis() - startTime < distance) {
    analogWrite(speed_motor1, Speed);
    digitalWrite(forward_motor1, LOW);
    digitalWrite(backward_motor1, HIGH);
    analogWrite(speed_motor2, Speed);
    digitalWrite(forward_motor2, LOW);
    digitalWrite(backward_motor2, HIGH);
    Serial.println("backward");
  }
  Stop();
}

void left(int distance) {
  unsigned long startTime = millis();
  while (millis() - startTime < distance) {
    analogWrite(speed_motor1, Speed);
    digitalWrite(forward_motor1, HIGH);
    digitalWrite(backward_motor1, LOW);
    analogWrite(speed_motor2, Speed);
    digitalWrite(forward_motor2, LOW);
    digitalWrite(backward_motor2, HIGH);
    Serial.println("left");
  }
  Stop();
}

void right(int distance) {
  unsigned long startTime = millis();
  while (millis() - startTime < distance) {
    analogWrite(speed_motor1, Speed);
    digitalWrite(forward_motor1, LOW);
    digitalWrite(backward_motor1, HIGH);
    analogWrite(speed_motor2, Speed);
    digitalWrite(forward_motor2, HIGH);
    digitalWrite(backward_motor2, LOW);
    Serial.println("right");
  }
  Stop();
}

void loop(){
  forward(30)

}
void loop() {
  forward();
  // put your main code here, to run repeatedly:

}
