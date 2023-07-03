# Timer3_FastPWM

This C++ class provides functionality for generating PWM signals with Timer3 on an Arduino Leonardo board.

## Description

The `Timer3_FastPWM` class allows you to generate PWM signals on pin 5 of the Arduino Leonardo. It utilizes Timer3 and provides methods for initializing the counter, setting the duty cycle, and retrieving the current duty cycle value.

The class offers the following settings in the constructor:
- `prescaler` ($`N_{Prescaler}`$): A divider for Timer3. You can choose from the available enumerated values defined in the `Prescaler` enumeration.
- `top_limit` ($`k_{TOP}`$): The maximum value up to which the Timer3 counter counts. This value should be less than 2047.

## Usage

To use the `Timer3_FastPWM` class, follow these steps:

1. Include the `TIMER3_FAST_PWM.h` header file in your Arduino sketch.
2. Create an instance of the `Timer3_FastPWM` class, providing the desired `prescaler` and `top_limit` values in the constructor.
3. Call the `begin_Pin5()` method to initialize the counter and configure pin 5 as the PWM output. Optionally, you can set the `invert` parameter to `true` to invert the PWM signal.
4. Use the `analogWrite_Pin5()` method to set the duty cycle of the PWM signal. Pass a value between 0 and the set `top_limit`.
5. Retrieve the current duty cycle value using the `get_value_Pin5()` method if needed.

## Formulas

The following formulas can be used to calculate various aspects of the PWM signal:

- Duty Cycle:
  $`D = k_{REG} / k_{TOP} * 100 \% `$

- Resolution of the Duty Cycle:
  $`R_{\%PWM} = 100% / k_{TOP}`$

- Frequency of PWM:
  $`f_{PWM} = f_{Mikrocontroller} / (N_{Prescaler} * k_{TOP})`$

Where:
- $`D`$ : Duty cycle in percentage
- $`k_{REG}`$ : Value for comparison with the counter value to set a PWM duty cycle
- $`k_{TOP}`$ : Value to set the PWM frequency (top limit)
- $`R_{\%PWM}`$ : Resolution of the duty cycle in percentage
- $`f_{PWM}`$ : Frequency of the PWM signal
- $`f_{Mikrocontroller}`$ : Operating frequency of the microcontroller
- $`N_{Prescaler}`$ : Counter prescaler

## Example

Here's an example usage of the `Timer3_FastPWM` class:

```cpp
#include <Arduino.h>
#include "TIMER3_FAST_PWM.h"

// Create an instance of Timer3_FastPWM with a prescaler of PS_64 and top_limit of 1023
Timer3_FastPWM pwm(PS_64, 1023);

void setup() {
  // Initialize pin 5 for PWM output, with the PWM signal not inverted
  pwm.begin_Pin5(false);
}

void loop() {
  // Set the duty cycle to 50% (512) on pin 5
  pwm.analogWrite_Pin5(512);
  delay(1000);

  // Set the duty cycle to 25% (256) on pin 5
  pwm.analogWrite_Pin5(256);
  delay(1000);
}
