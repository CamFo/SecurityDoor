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

// Déclaration de fonction privée
void piloteSerinPYQ_writeBit(bool value);


void piloteSerinPYQ_writeByte(unsigned char value)
{
    int compt;
    compt = 0;
    for(compt = 0; compt < 8; compt++)
    {
        if((value & 0x80) == 0x80)
        {
            piloteSerinPYQ_writeBit(1);
        }
        else
        {
            piloteSerinPYQ_writeBit(0);
        }
        value = value << 1;
    }
}

void piloteSerinPYQ_writeBit(bool value)
{
    digitalWrite(PILOTESERINPYQ_BROCHE, LOW); 
    digitalWrite(PILOTESERINPYQ_BROCHE, HIGH);
    digitalWrite(PILOTESERINPYQ_BROCHE, value);
    delayMicroseconds(80); // On attend 80 micro sec avant d'envoyé le prochain bit 
}

void piloteSerinPYQ_initialise(void)
{
    pinMode(27,OUTPUT);
    digitalWrite(27, LOW);  
    delay(1);

    piloteSerinPYQ_writeByte(0x80);
    piloteSerinPYQ_writeByte(0x8A);
    piloteSerinPYQ_writeByte(0x88);
    piloteSerinPYQ_writeBit(0);
    delay(1);
}