/*
 *  main.c
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Simple Board Initialization and sleep. Interrupts enabled PORT1 to toggle LEDs on button press
 *
 *  Notes:
 *      No debounce implemented on button press
 *      Board is initialized to lowest power state. No modules enabled.
 */
#include <msp.h>
#include "msp_compatibility.h"

void initPorts(void);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    initPorts();
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31); //Interrupt Set Enable Register Bit for Port 1. Must be set along with PxIE
    __enable_interrupts();

    while(1)
    {
        __deep_sleep();
    }

}

void initPorts(void)
{
    P1OUT = 0x00;
    P1DIR |= BIT7|BIT6|BIT5|BIT3|BIT2|BIT0;
    P1OUT &= ~BIT0; //Reset BIT0 to low, BIT0 gets initialized high by setting direction.
    P1OUT |= BIT4|BIT1; //Input with pullup resistor
    P1REN |= BIT4|BIT1; //Input with pullup resistor
    P1IE |= BIT4|BIT1; //Interrupt enable
    P1IES |= BIT4|BIT1; //Interrupt Edge Select
    P1IFG = 0x00;

    P2OUT = 0x00;
    P2DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;
    P2OUT &= ~BIT2|~BIT1|~BIT0;

    P3OUT = 0x00;
    P3DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P4OUT = 0x00;
    P4DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P5OUT = 0x00;
    P5DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P6OUT = 0x00;
    P6DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P7OUT = 0x00;
    P7DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P8OUT = 0x00;
    P8DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P9OUT = 0x00;
    P9DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

    P10OUT = 0x00;
    P10DIR |= BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

}
