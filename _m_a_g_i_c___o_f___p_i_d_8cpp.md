
# File MAGIC\_OF\_PID.cpp


[**File List**](files.md) **>** [**MAGIC\_OF\_PID.cpp**](_m_a_g_i_c___o_f___p_i_d_8cpp.md)

[Go to the source code of this file.](_m_a_g_i_c___o_f___p_i_d_8cpp_source.md)



* `#include <PID.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|   | [**end\_time**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-end-time)  <br> |
|   | [**flow\_rate**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-flow-rate)  <br> |
|   | [**integral**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-integral)  <br> |
|   | [**output**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-output)  <br> |
|   | [**pid\_control**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-pid-control)  <br> |
|   | [**previous\_error**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-previous-error)  <br> |
|   | [**pulses\_counter**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-pulses-counter)  <br> |
|   | [**start\_time**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#variable-start-time)  <br> |


## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**control\_propeller**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#function-control-propeller)  <br> |
|   | [**loop**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#function-loop) () <br> |
|   | [**pulse\_increment**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#function-pulse-increment)  <br> |
|   | [**read\_flowrate**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#function-read-flowrate)  <br> |
|   | [**setup**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#function-setup) () <br> |







## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DESIRED\_FLOW\_RATE**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-desired-flow-rate)  <br> |
| define  | [**FLOW\_METER\_PIN**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-flow-meter-pin)  <br> |
| define  | [**MAX\_FLOW\_RATE**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-max-flow-rate)  <br> |
| define  | [**OUTPUT\_PIN**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-output-pin)  <br> |
| define  | [**k\_derivative**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-k-derivative)  <br> |
| define  | [**k\_integral**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-k-integral)  <br> |
| define  | [**k\_proportional**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-k-proportional)  <br> |
| define  | [**time\_interval**](_m_a_g_i_c___o_f___p_i_d_8cpp.md#define-time-interval)  <br> |

## Public Attributes Documentation


### variable end\_time 


```cpp
unsigned long end_time;
```



### variable flow\_rate 


```cpp
float flow_rate;
```



### variable integral 


```cpp
float integral;
```



### variable output 


```cpp
float output;
```



### variable pid\_control 


```cpp
PID pid_control(k_proportional, k_integral, k_derivative, time_interval, MAX_FLOW_RATE);
```



### variable previous\_error 


```cpp
float previous_error;
```



### variable pulses\_counter 


```cpp
long long pulses_counter;
```



### variable start\_time 


```cpp
unsigned long start_time;
```


## Public Functions Documentation


### function control\_propeller 
void control_propeller	(	float 	output	)	


```cpp
give command to the flow meter to control its speed based on the output of PID

Parameters
output	is the PID output value
```



### function loop 
void loop( )	
```cpp

```



### function pulse\_increment 

void pulse_increment(void)

```cpp
this function increments the pulse counter for every interrupt
```



### function read\_flowrate 

float read_flowrate	(void)

```cpp
calculates the flow rate for the control time interval in seconds
Returns
 flow rate
```



### function setup 
void setup ( )	

```

```


## Macro Definition Documentation



### define DESIRED\_FLOW\_RATE 


```cpp
90.0
```



### define FLOW\_METER\_PIN 


```cpp
A0
```



### define MAX\_FLOW\_RATE 


```cpp
140.0
```



### define OUTPUT\_PIN 


```cpp
3
```



### define k\_derivative 


```cpp
0.2
```



### define k\_integral 


```cpp
0.5
```



### define k\_proportional 


```cpp
1.0
```



### define time\_interval 


```cpp
0.01
```



------------------------------
The documentation for this class was generated from the following file `C:/Users/Public/Magic_of_pid/MAGIC_OF_PID.cpp`