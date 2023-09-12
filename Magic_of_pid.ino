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
