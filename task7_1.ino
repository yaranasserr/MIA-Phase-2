#include <Encoder.h>
#define EncoderA 2
#define EncoderB 3
#define motor_speed 9
#define motor_direction 8

int speed_value =0;
int current_value= 0;
float smoothed_value=0;
float smoothing_factor =0.9;
Encoder myEncoder(EncoderA,EncoderB);
volatile long encoder_position =0;

int previous_A_state = LOW;
int previous_B_state = LOW;

void setup() {
  // put your setup code here, to run once:
attachInterrupt(digitalPinToInterrupt(EncoderA),updateEncoder,CHANGE);
attachInterrupt(digitalPinToInterrupt(EncoderB), updateEncoder, CHANGE);
pinMode(motor_direction,OUTPUT);
pinMode(motor_speed,OUTPUT);

}

void loop() {
    int motor_speed_reading =encoder_position;
  current_value = motor_speed_reading;
  smoothed_value = (smoothing_factor*current_value)+((1 - smoothing_factor)* smoothed_value);
  
  digitalWrite(motor_direction,HIGH);//if it is high its froward if its low it goes backwards
  speed_value=int(smoothed_value);
  digitalWrite(motor_speed,speed_value);
  
  Serial.print("smoothed Motor speed:");
  Serial.println(smoothed_value);
}
void updateEncoder(){
    int A_state = digitalRead(EncoderA);
  int B_state = digitalRead(EncoderB);

if ((previous_A_state == LOW && A_state == HIGH) || (previous_B_state == LOW && B_state == HIGH)) {
    if (A_state != B_state) {
      encoder_position++;
    } else {
      encoder_position--;
    }
   previous_A_state = A_state;
  previous_B_state = B_state;
}
}
