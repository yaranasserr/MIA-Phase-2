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