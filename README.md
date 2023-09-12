# MAGIC OF PID

---

## PID definition:

PID (Proportional-Integral-Derivative) is a widely used control algorithm. It is designed to regulate a process variable by continuously adjusting a control signal based on the error between the desired setpoint and the actual value of the variable.

The PID controller consists of three main components:

1. Proportional (P) term: It provides a control output proportional to the current error. The P term helps the controller respond quickly to changes in the error, but it may result in a steady-state error.
2. Integral (I) term: It integrates the error over time and helps eliminate steady-state error. The I term is responsible for continuously adjusting the control output based on the historical error values.
3. Derivative (D) term: It calculates the rate of change of the error and adjusts the control output accordingly. The D term helps in dampening the response and reducing overshoot or oscillations.

---

## Anti-windup definition:

Anti-windup is a technique used in PID controllers to prevent overshoot or instability when the control output saturates or reaches its limits. Saturation can occur when the control signal is clamped within a specific range, such as when driving a motor or controlling a valve that has physical limits.

Clamping is a method of limiting the control output within a predefined range. It sets an upper and lower limit to prevent the control signal from exceeding certain boundaries. When the control output saturates due to clamping, the anti-windup mechanism comes into play.

---

## **PID library:**

### 1. Header File:

The header file (.h) contains the declarations and definitions of classes, methods, variables and constants of the PID class declarations.

The PID library includes one class only which is the PID class.

The following table contains the usage of each variable:

| variable | variable usage |
| --- | --- |
| derivative | contains the value of derivative  |
| output | contains the PID output |
| error | contains the current error of the system |
| integrator switch | Flag that acts as a switch to control the integrator as it turns it off at saturation point to prevent any windup. It holds the value of 1 by default  |
| KP | proportional gain |
| KI | integral gain |
| KD | derivative gain |
| DT | time interval of the PID control |
| MAX_RATE | maximum rate of the system |

The Header file code:

```arduino
#ifndef PID_h
#define PID_h
#include "Arduino.h"
class PID 
{
public:
    float derivative;
    float output;
    float error;
    int integrator_switch = 1;

private:
    float KP;
    float KI;
    float KD;
    float DT;
    float MAX_RATE;

public:
    PID(float kp,float ki,float kd,float dt,float flow_meter_max_rate);
    float calculate(float setpoint,float process_variable,float &previous_error,float &integral);
    float clamp(float output,float error);
};
#endif
```

---

### 2. Source File:

The source file contains the implementation of the functions and classes declared in the header file.

The description of each function:

### 1. PID:

Parameters:  

- kp
- ki
- kd
- dt
- flow_meter_max_rate

Description:

- PID function is the constructor of the class which takes the constants of the PID system and sets

them to its attributes.

Code:

```arduino
PID::PID(float kp,float ki,float kd,float dt,float flow_meter_max_rate)
    {
      KP = kp;
      KI = ki;
      KD = kd;
      DT = dt;
      MAX_RATE = flow_meter_max_rate;
    }
```

### 2. calculate:

Parameters:  

- setpoint
- process_variable
- previous_error
- integral

Returns:

- PID output

Description:

- The calculate function calculate the PID output by taking the following parameters setpoint which is the targeted PID value, process_variable which is the current input, address of previous_error which is the calculated error from the previous time interval to set its new value with no need of returning it again and the address of the integral.

Calculations:

- error which is equal to the difference between the targeted value and the current value.       **error = setpoint (SP) - process variable (PV)**
- integral which is equal to the sum of all errors multiplied by the time interval of the integration and this time interval could be between 1 ms to 100 ms.                                                    **integral = integral + error * dt**
- derivative value is equal to the difference between the current error and previous error divided by the time interval.                                                                                                             **derivative = (error - previous error) / dt**
- PID output value which is equal to the proportional gain multiplied by the proportional ( error ) value plus the integral gain multiplied by the integral value plus the derivative gain multiplied by the value of derivative. But the integral part is also multiplied by the integrator switch which could turn the integrator off when set to zero or on when set to one.                                              **output = KP * error + KI * integral * integrator switch + KD * derivative**                                       The following equation is used for calculating the PID output but using calculus:

$$
c(t) = Kp * e(t) + Ki * ∫e(t) dt + Kd * de(t)/dt
$$

- previous error should hold the value of the current error for the next calculation.
- Finally, we return the output after passing it to the clamp function.

Code:

```arduino
float PID::calculate(float setpoint,float process_variable,float &previous_error,float &integral)
    {
      error =  setpoint - process_variable;      
      integral += error * DT;                                   
      derivative = (error - previous_error) / DT;               
      output = KP * error + KI * integral * integrator_switch + KD * derivative; 
      previous_error = error;                                   
      return clamp(output,error);
    }
```

### 3. clamp:

 Parameters:  

- output
- error

Returns:

- PID final output

Description:

- The reason for this function is to be an anti-windup function which takes the output before               sending it as a command and compares it to the maximum rate of the system if it is greater than or  equal to this rate then it checks how the integrator handles this problem so, if the output sign and the error sign are the same then we should turn off the integrator and set the output to be the maximum value of the system else the integrator should be on and return the PID output.

Code:

```arduino
float PID::clamp(float output,float error)
    {
      if(output >= MAX_RATE)
        if((error > 0 && output > 0) || (error < 0 && output < 0))
        {
          integrator_switch = 0;
          return MAX_RATE;
        }
      integrator_switch = 1;
      return output;
    }
```

And this is the whole code of the Source File:

```arduino
#include "Arduino.h"
#include "PID.h"

PID::PID(float kp,float ki,float kd,float dt,float flow_meter_max_rate)
    {
      KP = kp;
      KI = ki;
      KD = kd;
      DT = dt;
      MAX_RATE = flow_meter_max_rate;
    }
    /**
     *@brief calculate the PID output value
     *@param setpoint the targeted setpoint
     *@param process_variable the current input value
     *@param previous_error the previous error for the derivative term
     *@param integral the integral term of PID control
     */
    float PID::calculate(float setpoint,float process_variable,float &previous_error,float &integral)
    {
      error =  setpoint - process_variable;                     //calculate the error = SP - PV
      integral += error * DT;                                   //integral = summation of all previous errors multiplied by the time interval
      derivative = (error - previous_error) / DT;               //derivative = ( current error - previous error) / time interval 
      output = KP * error + KI * integral * integrator_switch + KD * derivative; 
      previous_error = error;                                   //set the previous error to be the current error
      return clamp(output,error);
    }
    /**
     *@param output the PID output
     *@param error the PID current error
     *@brief checks if the output exceeded the maximum flow rate if true it compares the sign of the error and the PID output if the 
             are different this means that the integrator should be turned off to avoid any wind up
    */
    float PID::clamp(float output,float error)
    {
      if(output >= MAX_RATE)
        if((error > 0 && output > 0) || (error < 0 && output < 0))
        {
          integrator_switch = 0;
          return MAX_RATE;
        }
      integrator_switch = 1;
      return output;
    }
```

---

## Arduino code:

```arduino
#include <PID.h>
/**
 *@file Magic_of_PID.ino
 *@brief Arduino code for PID control of the Autonomous Planet Cleaner machine APC 
 */
 

//constants
#define FLOW_METER_PIN A0   
#define OUTPUT_PIN 3             //pwm pin
#define MAX_FLOW_RATE 140.0      //flow meter maximum flow rate for the Mid Range thermal mass air flow meters 1 -> 140 CFM
#define DESIRED_FLOW_RATE 90.0   //targeted flow rate 90 CFM  
#define k_proportional 1.0       //proportional gain
#define k_integral 0.5           //integral gain
#define k_derivative 0.2         //derivative gain
#define time_interval 0.01       //PID time interval

//create a new inistance of PID class
PID pid_control(k_proportional,k_integral,k_derivative,time_interval,MAX_FLOW_RATE);
//number of pulses from the flow meter
long long pulses_counter = 0;

//start time and end time of the measurment
unsigned long start_time = 0.0;
unsigned long end_time = 0.0;

float flow_rate = 0.0;      //flow rate in CFM
float output = 0.0;         //PID output
float previous_error = 0.0; //the previous error of the PID
float integral = 0.0;       //integral term of PID

void setup() {
  //set the flow meter pin as input with an internal pull up resistor
  pinMode(FLOW_METER_PIN,INPUT_PULLUP);
  //attach interrupt to the flow meter and calls pulse_increment method to trigger the interrupt when the pin goes from low to high
  attachInterrupt(digitalPinToInterrupt(FLOW_METER_PIN),pulse_increment,RISING);
  //start serial communication
  Serial.begin(9600);
}

void loop() {
  //read the flow rate
  flow_rate = read_flowrate();
  //calculate the PID output
  output = pid_control.calculate(DESIRED_FLOW_RATE,flow_rate,previous_error,integral);
  //apply the output to the flaw meter

  control_propeller(output);

}

/**
 * @brief this function increments the pulse counter for every interrupt 
*/
void pulse_increment(void)
{
  pulses_counter += 1;
}

/**
 *@return flow rate
 *@brief calculates the flow rate for the control time interval in seconds
*/
float read_flowrate(void)
{
  float time_measurment;

  start_time = millis();          //start measuring interval
  pulses_counter = 0;             //reset the pulse counter
  delay(1000 * time_interval);    /*delay for the measuring interval based on the time interval in seconds.
                                    this delay function would stop the code from execution except for the interrupts that would
                                    calculate the number of pulses in the guven time interval*/
  end_time = millis();            //end measuring interval
  time_measurment = (end_time - start_time) / (1000.0);   //calculate the time interval in seconds
  return pulses_counter / time_measurment;                                //return the flow rate
}

/**
 *@param output is the PID output value
 *@brief give command to the flow meter to control its speed based on the output of PID
*/
void control_propeller(float output) 
{
  // Map the PID output speed value to the desired range for controlling the flow meter
  int required_speed = map(output, -255, 255, 0, 255);

  // Apply the required speed to control the flow meter to change its speed and change the flow rate to the desired flow rate
  analogWrite(OUTPUT_PIN, required_speed);
}
```