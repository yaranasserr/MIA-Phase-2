#define speed_motor1 6
#define speed_motor2 5
#define forward_motor1 2
#define backward_motor1 7
#define forward_motor2 3
#define backward_motor2 4
int Speed = 80;
void setup() {
  pinMode(speed_motor1, OUTPUT);
  pinMode(speed_motor2, OUTPUT);
  pinMode(forward_motor1, OUTPUT);
  pinMode(backward_motor1, OUTPUT);
  pinMode(forward_motor2, OUTPUT);
  pinMode(backward_motor2, OUTPUT);

}

void loop() {
  
}

void forward()
{
  analogWrite(speed_motor1, Speed);
  digitalWrite(forward_motor1, HIGH);
  digitalWrite(backward_motor1, LOW);
  analogWrite(speed_motor2, Speed);
  digitalWrite(forward_motor2, HIGH);
  digitalWrite(backward_motor2, LOW);
  Serial.println("forward");
}
void backward()
{
  analogWrite(speed_motor1, Speed);
  digitalWrite(forward_motor1, LOW);
  digitalWrite(backward_motor1, HIGH);
  analogWrite(speed_motor2, Speed);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(backward_motor2, HIGH);
  Serial.println("backward");
}
void left()
{
  analogWrite(speed_motor1, Speed);
  digitalWrite(forward_motor1, HIGH);
  digitalWrite(backward_motor1, LOW);
  analogWrite(speed_motor2, Speed);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(backward_motor2, HIGH);
  Serial.println("left");
}
void right()
{
  analogWrite(speed_motor1, Speed);
  digitalWrite(forward_motor1, LOW);
  digitalWrite(backward_motor1, HIGH);
  analogWrite(speed_motor2, Speed);
  digitalWrite(forward_motor2, HIGH);
  digitalWrite(backward_motor2, LOW);
  Serial.println("right");
}
void Stop()
{
  digitalWrite(forward_motor1, LOW);
  digitalWrite(backward_motor1, LOW);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(backward_motor2, LOW);
  Serial.println("stop");
}
