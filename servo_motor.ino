#include <Servo.h>// header file for controlling servo
Servo servo_motor;//defining the name usage as servo itself
void setup() {
  Serial.begin(9600);
  servo_motor.attach(2);//setup

}
void servo_motor_control()//function to cotrol servo motor
{
  int i;
  for(i=0;i<90;i++)//loop for controlling time of rising  moving (90 range of motion)
  {
    servo_motor.write(i);
  	delay(100); //depending on time needed for range of motion
  }
  for(i=90;i>0;i--) //loop for controlling time of motion in opposite direction
  {
    servo_motor.write(i);
  	delay(100);
  }
  	
    
}

void loop() 
{
      
}
