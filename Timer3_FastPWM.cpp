#include "Timer3_FastPWM.h"

Timer3_FastPWM::Timer3_FastPWM(Prescaler prescaler, uint16_t top_limit)
{
    this->configured = false;
    this->prescaler = prescaler;
    this->top_limit = top_limit;
}

void Timer3_FastPWM::common_configuration()
{
    TCCR3A |= _BV(WGM31); // Configure Fast PWM with ICR3 as TOP limit
    TCCR3A &= ~_BV(WGM30); // Configure Fast PWM with ICR3 as TOP limit
    TCCR3B = 0;
    TCCR3B |= _BV(WGM32) | _BV(WGM33); // Configure Fast PWM with ICR3 as TOP limit
    TCCR3B = (0b11111000 & TCCR3B) | this->prescaler; // Set the timer3 prescaler
    ICR3 = this->top_limit; // Set the TOP limit of the timer (Overflow)
    this->configured = true;
}

void Timer3_FastPWM::begin_Pin5(bool invert)
{
    if (!this->configured)
        this->common_configuration();
    OCR3A = 0; // Set a PWM of 0% for the pin 5
    // Activate the Fast PWM on pin 5
    TCCR3A |= _BV(COM3A1);
    // Invert the signal if necessary
    if (invert)
        TCCR3A  |= _BV(COM3A0);
    else
        TCCR3A &= ~_BV(COM3A0);
    pinMode(5, OUTPUT); // Configure the pin as output
}

void Timer3_FastPWM::analogWrite_Pin5(uint16_t value)
{
    this->value_Pin6 = value;
    OCR3A = value;
}

uint16_t Timer3_FastPWM::get_value_Pin5()
{
    return this->value_Pin5;
}