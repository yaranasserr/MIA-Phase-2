#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>
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