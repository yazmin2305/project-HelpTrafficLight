/* 
 * File:   main.c
 * Author: MFCAICEDO
 *
 * Created on 1 de marzo de 2022, 12:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>
#include "fuses.h"

#define _XTAL_FREQ 80000000
#define MOTORIN1 PORTBbits.RB0
#define MOTORIN2 PORTBbits.RB1
#define MOTORENABLE PORTBbits.RB7
#define IN 1
#define OUT 0
#define ON 1
#define OFF 0

/*
 * main
 */
int main(int argc, char** argv) {
    //Settings
    OSCCON=0b01110010;
    ADCON1 = 0x0F;
    //MOTOR 
    MOTORIN1 = OFF; 
    MOTORIN2 = OFF; 
    MOTORENABLE = OFF; 
    int BLUETOOTH = ON; //provicional 
    
    while(1){
        
        __delay_ms(20);
        if(BLUETOOTH == ON){
            MOTORENABLE = ON;
            MOTORIN1 = ON;
            MOTORIN2 = OFF;
        }else{
             MOTORENABLE = OFF;
        }
    }
    
    return (EXIT_SUCCESS);
}
