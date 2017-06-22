/*
 *  main.c
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Simple project that echos serial input on Backchannel UART. Also includes PORT1 ISR for LED toggle on button press.
 *
 *  Notes:
 *      No debounce implemented on button press.
 *
 */
#include <msp.h>
#include "msp_compatibility.h"

void initPorts(void);
void initBCUART(void);
void populateNVIC(void);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    initPorts();
    populateNVIC();
    initBCUART();

    __enable_interrupts();

    while(1)
    {
        __sleep();
    }

}

void initBCUART(void)
{
    P1SEL0 |= BIT3|BIT2; //Enable peripheral pins
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; //Put eUSCI_A0 in reset state
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST | EUSCI_A_CTLW0_SSEL__SMCLK; //Use SMCLK, stay in reset
    EUSCI_A0->BRW = 20;                     // 3,000,000/16/9600 = 20
    EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16; //Oversampling mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt
}

void populateNVIC(void)
{
    //This function exists to populate the Nested Vector Interrupt Controller with proper IRQ enable bits

    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31); //Interrupt Set Enable Register Bit for Port 1. Must be set along with PxIE
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);
}

void initPorts(void)
{
    //Initializes MSP-EXP432P401R board to lowest power consumption state.
    //For portability, any additional port mapping should be performed in separate functions after this is executed.

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
    P2OUT &= ~BIT2|~BIT1|~BIT0; //RGBLED Bits

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
