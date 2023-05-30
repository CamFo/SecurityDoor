/**
 * @file piloteSerinPYQ.cpp
 * @author Camille Fortin
 * @brief 
 * @version 0.1
 * @date 2023-05-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>

#include "main.h"
#include "piloteSerinPYQ.h"

void piloteSerinPYQ_WriteBit(bool value)
{
    digitalWrite(27, LOW);  

}


void piloteSerinPYQ_initialise(void)
{
    pinMode(27,OUTPUT);
    digitalWrite(27, LOW);  
    delay(1);


}