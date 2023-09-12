
# Class PID


[**Class List**](annotated.md) **>** [**PID**](class_p_i_d.md)





* `#include <PID.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|   | [**derivative**](class_p_i_d.md#variable-derivative)  <br> |
|   | [**error**](class_p_i_d.md#variable-error)  <br> |
|   | [**integrator\_switch**](class_p_i_d.md#variable-integrator-switch)  <br> |
|   | [**output**](class_p_i_d.md#variable-output)  <br> |


## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PID**](class_p_i_d.md#function-pid)  <br> |
|   | [**calculate**](class_p_i_d.md#function-calculate)  <br> |
|   | [**clamp**](class_p_i_d.md#function-clamp)  <br> |








## Public Attributes Documentation


### variable derivative 


```cpp
float PID::derivative;
```



### variable error 


```cpp
float PID::error;
```



### variable integrator\_switch 


```cpp
int PID::integrator_switch;
```



### variable output 


```cpp
float PID::output;
```


## Public Functions Documentation


### function PID 
PID (float kp,float ki,float kd,float dt,float flow_meter_max_rate)		

```

```



### function calculate 
float PID::calculate(float setpoint,
float process_variable,float & previous_error,float & integral )	

```cpp
calculate the PID output value

Parameters
setpoint	the targeted setpoint
process_variable	the current input value
previous_error	the previous error for the derivative term
integral	the integral term of PID control
```



### function clamp 

float PID::clamp	(	float 	output,
float 	error 
)	

```
checks if the output exceeded the maximum flow rate if true it compares the sign of the error and the PID output if the are different this means that the integrator should be turned off to avoid any wind up

Parameters
output	the PID output
error	the PID current error

```



------------------------------
The documentation for this class was generated from the following file `C:/Users/Public/Magic_of_pid/PID.h`