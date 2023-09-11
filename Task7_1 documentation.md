# Task7_1

# Cytron Motor Driver:

the cytron motor driver is a great motor driver to use .on the contrary to the other drivers like L298N it has some nique features

- Cytron motor drivers are designed to control DC motors, stepper motors, or even brushless DC motors, depending on the model. They provide the necessary circuitry to drive these motors effectively.
- It is designed to drive high current brushed DC motor up to 13A continuously and 30A peak
- due to increasing the current it also increases the torqe of the motor

# the task:

in this task we are using a motor driver and a brushed dc motor and we are adding a smoothing filter.

to add the smoothing filter we need to use the encoder to read the values and smooth it to be able to make a software soft start filter.

# Code:

### initalizing:

```arduino
#include <Encoder.h>
#define EncoderA 2
#define EncoderB 3
#define motor_speed 9
#define motor_direction 8

int speed_value =0;
int current_value= 0;
float smoothed_value=0;
float smoothing_factor =0.9;
volatile long encoder_position =0;
int previous_A_state = LOW;
int previous_B_state = LOW;

Encoder myEncoder(EncoderA,EncoderB);
```

here we are identifying the variables we are going to use.

first we included the encoder library,then we are defining the encoder pins.

then we are defining the motor speed pin and also the motor direction pin(either clockwise or anticlockwise).

then we are verifing the variable we are going to use in the filter and to get a more smoothed value

lastly we are making an instance for the encoder pointing at the encoderA and encoderB

### setup and loop:

```arduino
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
```

in the setup we are attaching interupts to the encoders and we are defining the mpotor speed and direction as outputs

in the loop we start by filtering and smothing the values by reading the values of the motor by the encoder and then running it through an equation

```arduino
  smoothed_value = (smoothing_factor*current_value)+((1 - smoothing_factor)* smoothed_value);
```

in this line we smooth the value by using the smoothing factor which is identified acoding to the application used so we here need it closer to 1 to insure stability.

then we are making the smoothed value as integer to use it in controlling the motor speed.

### function:

```arduino
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
```

in this function it is used to manipulate the encoders and increase or decrease the count that help in making the filter.also it monitors the state of the pins to help read the encoder value

# Is this motor suitable for this application?

In this application we are using a brushed dc motor.

looking through other types of motors the Dc brushed motor is the most suitable with the most upsides and the least downsides.

- the brushed dc motor offer the simplict control over the motor speed and direction .
- they are widely found
- they are the cheap.
- they offer a more simple control method over the brushless motors
- even though they need maintance and have shorter life span than brushless motors its benefits outway its drawbacks

In summary, a DC brushed motor can be a suitable choice for a vacuum or suction application, especially for applications where simplicity of control and cost-effectiveness are important.