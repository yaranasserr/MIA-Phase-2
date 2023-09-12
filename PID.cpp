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