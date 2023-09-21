#include <MPU6050.h>    
#include <Wire.h>                            // Wire library require for I2C protocol
#include <I2Cdev.h>                          // Include I2C protocol



MPU6050 gyroAccelTemp;                       // Declare a MPU6050 object instance
//Define the properties of the MPU-6050 (IMU)
float gyroDegree;
#define GYRO_Z_OFFSET 16
float previousTime;

int count = 0; // green spots
float ultra = 0; //
int rot= 0;//
int angle;


void setup() {
  Serial.begin(115200);                      // Initialize Serial Communication

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
  

}

void loop() {
  if(count==0)
  {
    previousTime = micros();
    angle = return_angle();
    while(angle<90)
    {
      Speed = Speed  - abs(angle)*.1;
//      right();
      angle = return_angle();
    }
   // Stop();
    
    ultra = get_distance;
    while(ultra>5)
    {
      Speed = Speed  - abs(ultra)*.1;
   //   forward();
      ultra = get_distance;
    }
    //Stop();
  }
  
}



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
