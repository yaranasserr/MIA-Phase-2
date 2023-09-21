#include <Wire.h>
#include <MPU6050.h>
#include <I2Cdev.h>
//including Functions
#include "Infrared.ino"
#include "IMU.ino"
#include "movement.ino"
#include "ultra.ino"

// Function declarations
// void read_color();
// void detect_color(uint16_t ambient_light, uint16_t red_light, uint16_t green_light, uint16_t blue_light);
// float return_angle();
// void forward(int distance);
// void backward(int distance);
// void left(int distance);
// void right(int distance);
// void Stop();
// long get_distance();
// void avoidCollision(int desiredDistance);

// Pin definitions
#define speed_motor1 3
#define speed_motor2 5
#define forward_motor1 2
#define backward_motor1 4
#define forward_motor2 6
#define backward_motor2 7

const int trigPin = 8;
const int echoPin = 9;

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

void loop() {
    // Step 1: Move forward downward from mid of blue to green 66 cm 
    forward(66); 
    // Step 2: Use ultrasonic sensor to prevent hitting the fence (margin 5 cm)
    avoidCollision(4.5); 
    // Step 3: Move backward upward to reach the upper right using ultrasonic sensor to detect 1.4m
    int distance_to_upper_right = 150;
    while (get_distance() > distance_to_upper_right) {
      backward(145)); // 
    }
    forward(30)
    Stop();
  
}
