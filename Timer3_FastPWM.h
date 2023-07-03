/*

Description:

Class for generating PWM signals with timer 3.

The following settings are available in the constructor:
    • prescaler: divider for Timer3. An enumeration Prescaler is defined for this setting with possible adjustable values.
    • top_limit: TOP value up to which the Timer3 counter counts. Should be less than 2047.

With this counter, pins 5 in the Arduino Leonardo can be used as PWM output. The following methods are available for each pin:
    • begin_Pin5: initializes the counter and sets the output pin. If TRUE is given the PWM is invertet.
    • analogWrite_Pin5: sets the duty cycle of the PWM signal. The value can be from 0 up to the set top_limit.
    • get_value_Pin5: returns the current value for the duty cycle setting.

Formula to calculate the duty cycle:

D = k_REG / k_TOP · 100 %

Formula to calculate the resoluction of the duty cycle

R_%,PWM = 100% / k_TOP 

Formula to calculate the frecueny when using f_Mikrocontroller:

f_PWM = f_Mikrocontroller / (N_Prescaler · k_TOP)

Symbol              Unit    Description
-----------------------------------------------------------------------------
D	                %	    Duty cycle
k_REG	            -	    Valuel for comparison with the counter value to set a PWM duty cycle
k_TOP	            -	    Value to set the PWM frequency
R_%,PWM	            %	    Resolution of the duty cycle
f_Mikrocontroller	Hz	    Operating frequency of the microcontroller
N_Prescaler	        -	    Counter prescaler

Author: Alejandro Miguel Kölbl
Date: 25.04.2023

*/

#ifndef TIMER3_FAST_PWM
#define TIMER3_FAST_PWM

#include <Arduino.h>

/*
 * PS ist the configured Prescaler and F the desired frequency
 * 
 * TOP Limit = (16MHz / (PS * F)) - 1
 * TOP Limit must be samaller than 65535
 * 
 * Value range 0 - TOP Limit
*/

class Timer3_FastPWM
{
    public:
        enum Prescaler {PS_1 = 1,
                        PS_8 = 2,
                        PS_64 = 3,
                        PS_256 = 4,
                        PS_1024 = 5};

        Timer3_FastPWM(Prescaler prescaler, uint16_t top_limit);
        void begin_Pin5(bool invert);
        void analogWrite_Pin5(uint16_t value);
        uint16_t get_value_Pin5();

    private:
        bool configured;
        Prescaler prescaler;
        uint16_t top_limit;
        uint16_t value_Pin5;
        void common_configuration();
};

#endif