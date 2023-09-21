#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <MPU6050.h>
#include <I2Cdev.h>

// Function declarations
void read_color();
void detect_color(uint16_t ambient_light, uint16_t red_light, uint16_t green_light, uint16_t blue_light);
float return_angle();
void forward(int distance);
void backward(int distance);
void left(int distance);
void right(int distance);
void Stop();
long get_distance();
void avoidCollision(int desiredDistance);

// Pin definitions
#define speed_motor1 6
#define speed_motor2 5
#define forward_motor1 2
#define backward_motor1 7
#define forward_motor2 3
#define backward_motor2 4

const int trigPin = 9;
const int echoPin = 10;
int Speed = 80;

//Sensor for color detection
SparkFun_APDS9960 apds = SparkFun_APDS9960();

//global variables
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

//counters for labels
int green_cntr = 0;
int yellow_cntr = 0;
int gray_cntr = 0;
int red_cntr = 0;

//IMU decleration
MPU6050 gyroAccelTemp;
float gyroDegree;
#define GYRO_Z_OFFSET 16
float previousTime;

int count = 0;
float ultra = 0;
int rot= 0;
int angle;
//..........................//
void setup() {

  Serial.begin(9600);
  apds.init();
  apds.enableLightSensor();
  
  // Wait for initialization and calibration to finish
  delay(500);
   // Initialize the IMU
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  gyroAccelTemp.initialize();

  // Verify IMU connection
  Serial.println("Testing device connections...");
  Serial.println(gyroAccelTemp.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  gyroAccelTemp.CalibrateGyro();                  // Fully calibrate gyro in about 15 loops
  Serial.println("Calibration complete");         // Notify when calibration is complete
  /* The following will NOT get rid of the noise produce by the IMU but they will ensure that
      the average values are at 0 to a certain extent
      (Refer to the IMU Error Determination code and the MPU6050 tutorial video for more details)
  */
  // Set Gyroscope Offsets
  gyroAccelTemp.setZGyroOffset(GYRO_Z_OFFSET);    // Set the Z gyroscope offset

  // IMPORTANT: If you do not calibrate after setting your offset, there will be error
  gyroAccelTemp.CalibrateGyro(6);                 // Fine Tuning purposes of gyroscope
  Serial.println("Fine Tuning Complete");  // Notify when fine tuning is complete

  pinMode(speed_motor1, OUTPUT);
  pinMode(speed_motor2, OUTPUT);
  pinMode(forward_motor1, OUTPUT);
  pinMode(backward_motor1, OUTPUT);
  pinMode(forward_motor2, OUTPUT);
  pinMode(backward_motor2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void read_color(){
  // Read the light levels (ambient, red, green, blue)
  apds.readAmbientLight(ambient_light);
  apds.readRedLight(red_light);
  apds.readGreenLight(green_light);
  apds.readBlueLight(blue_light);

  detect_color(ambient_light,red_light,green_light,blue_light);

}
void detect_color(uint16_t ambient_light,uint16_t red_light,uint16_t green_light,uint16_t blue_light){
  //warning!
  //light values should be changed after detecting each color
  if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      green_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      red_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      yellow_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      gray_cntr++;
    }
  else{
    return;
  }
}
//IMU sensor
float return_angle():
{
   float gyroZ = gyroAccelTemp.getRotationZ() / 131.0;  
   float timeForOneLoop = micros() - previousTime;
    //Serial.println(timeForOneLoop);
    gyroDegree += gyroZ * timeForOneLoop / 1000000.0;
   // NOTE: Try and keep the following code close to the above if statement
   previousTime = micros();
   return gyroDegree;
}
//Motor Movement//
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

// void forward()
// {
//   analogWrite(speed_motor1, Speed);
//   digitalWrite(forward_motor1, HIGH);
//   digitalWrite(backward_motor1, LOW);
//   analogWrite(speed_motor2, Speed);
//   digitalWrite(forward_motor2, HIGH);
//   digitalWrite(backward_motor2, LOW);
//   Serial.println("forward");
// }
// void backward()
// {
//   analogWrite(speed_motor1, Speed);
//   digitalWrite(forward_motor1, LOW);
//   digitalWrite(backward_motor1, HIGH);
//   analogWrite(speed_motor2, Speed);
//   digitalWrite(forward_motor2, LOW);
//   digitalWrite(backward_motor2, HIGH);
//   Serial.println("backward");
// }
// void left()
// {
//   analogWrite(speed_motor1, Speed);
//   digitalWrite(forward_motor1, HIGH);
//   digitalWrite(backward_motor1, LOW);
//   analogWrite(speed_motor2, Speed);
//   digitalWrite(forward_motor2, LOW);
//   digitalWrite(backward_motor2, HIGH);
//   Serial.println("left");
// }
// void right()
// {
//   analogWrite(speed_motor1, Speed);
//   digitalWrite(forward_motor1, LOW);
//   digitalWrite(backward_motor1, HIGH);
//   analogWrite(speed_motor2, Speed);
//   digitalWrite(forward_motor2, HIGH);
//   digitalWrite(backward_motor2, LOW);
//   Serial.println("right");
// }
void Stop()
{
  digitalWrite(forward_motor1, LOW);
  digitalWrite(backward_motor1, LOW);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(backward_motor2, LOW);
  Serial.println("stop");
}

long get_distance() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure distance
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void avoidCollision(int desiredDistance) {
  long distance = get_distance();

  // Check if the measured distance is less than desired distance
  if (distance < desiredDistance) {
    // Take action to avoid collision, change the direction of motion
  }
}



// void loop() {
//   if(count==0)
//   {
//     previousTime = micros();
//     angle = return_angle();
//     while(angle<90)
//     {
//       Speed = Speed  - abs(angle)*.1;
// //      right();
//       angle = return_angle();
//     }
//    // Stop();
    
//     ultra = get_distance;
//     while(ultra>5)
//     {
//       Speed = Speed  - abs(ultra)*.1;
//    //   forward();
//       ultra = get_distance;
//     }
//     //Stop();
//   }
  
// }

void loop() {
  if (count == 0) {
    // Step 1: Move forward downward 0.7 meter
    forward(70); 

    // Step 2: Use ultrasonic sensor to prevent hitting the fence (margin 5 cm)
    avoidCollision(5); 
    // Step 3: Move backward upward to reach the upper right using ultrasonic sensor to detect 1.4m
    int distance_to_upper_right = 140;
    while (get_distance() > distance_to_upper_right) {
      backward(10); // 
    }
    Stop();

    // Step 4: IR sensor at the back to detect the green label
    read_color(); 
    detect_green(ambient_light, red_light, green_light, blue_light); 

    //  green label is detected
    if (green_cntr > 0) {
      Speed = 50; // reduce the speed
    }

    // Step 5: Move downward 0.3 and rotate left
    forward(30); // Assuming 30 is the distance in units compatible with your sensor
    left(300);
    Stop();
  }
}
