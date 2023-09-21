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
void loop() {
  forward();
  // put your main code here, to run repeatedly:

}
