/* 
 * File:   main.c
 * Author: MFCAICEDO, ...
 *
 * Created on 22 de febrero de 2022, 10:07 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4550.h>
#include "fuses.h"

#define _XTAL_FREQ 80000000 //frecuencia 
#define LED_RED PORTDbits.RD0
#define LED_YELLOW PORTDbits.RD1
#define LED_GREEN PORTDbits.RD2
#define ULTRASONIC PORTEbits.RE0
#define SENSORPIR PORTAbits.RA0
#define BARRERA PORTDbits.RD4
#define ALARMA PORTDbits.RD3
#define IN 1
#define OUT 0
#define ON 1
#define OFF 0

/*
 *Funciones 
 */
void delaymsled_red_green(void);
void delaymsled_yellow(void);
void activarBarrera(void);
void piractivar(int flag);
/*
 * main
 */
int main(int argc, char** argv){
    //Settings -> 0 OUT  1 IN
    OSCCON=0b01110010;
    ADCON1 = 0x0F;
    TRISD = 0b00000000;
    //SENSOR PIR IN 
    TRISAbits.TRISA0=IN;
    SENSORPIR = IN;
    
    BARRERA = OFF;
    ALARMA = OFF;
    
    int contador = 0;
    while(1){
        
        if (contador != 0 ){
            //LED_YELLOW -> ON LED_GREEN -> OFF LED_RED -> OFF 
            LED_RED = OFF; 
            LED_YELLOW = ON;
            LED_GREEN = OFF;
            ALARMA = OFF;
            delaymsled_yellow(); 
        }
         //LED_YELLOW -> OFF LED_GREEN -> ON LED_RED -> OFF 
        LED_RED = OFF; 
        LED_YELLOW = OFF;
        LED_GREEN = ON;
        //Enable barrera 
        if(contador == 0){
            __delay_ms(7);
        }
        piractivar(0); //ENABLE PIR
        delaymsled_red_green();
        delaymsled_red_green();
    
        //LED_YELLOW -> ON LED_GREEN -> OFF LED_RED -> OFF 
        LED_RED = OFF; 
        LED_YELLOW = ON;
        LED_GREEN = OFF;
        delaymsled_yellow(); 
        
        //LED_YELLOW -> OFF LED_GREEN -> OFF LED_RED -> ON 
        LED_RED = ON;
        LED_YELLOW = OFF;
        LED_GREEN = OFF;
      
        piractivar(1);  //DISABLE PIR  
        delaymsled_red_green(); 
        delaymsled_red_green();
        
        contador++;
    }
    return (EXIT_SUCCESS);
}
/*
 *Se define el método delay para establecer el tiempo de espera 
 */
void delaymsled_red_green(void){
    __delay_ms(100);
}
void delaymsled_yellow(void){
    __delay_ms(30);
}
/*
 *Función para verificar el estado del pir 
 */
void piractivar(int flag){
    if (flag == 0){
        if (LED_GREEN == ON && SENSORPIR == ON){
            BARRERA = ON;
        }
    }else{
        if (LED_RED == ON &&  BARRERA == ON){
            BARRERA = OFF;
            if(SENSORPIR == ON){
               ALARMA = ON;
            }
        }
    }
}