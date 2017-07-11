/*
 *  main.c
 *
 *  Created on: July 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Simple project to demonstrate MSP432 I2C by reading WHO_AM_I data from an NXP FXOS8700 accelerometer/magnetometer sensor.
 *  The program uses polling for single byte reads and writes and is interrupt driven for multi-byte reads.
 *
 *  Notes:
 *      This basic I2C implementation does not perform any error checking for failed communications beyond a NACK in interrupt mode.
 *
 */

#include <msp.h>
#include "FXOS8700.h"
#include "i2c.h"

uint32_t i;
uint8_t txbufctr, rxbufctr;
uint8_t rxbuf[15], txbuf[5];
uint8_t TXByteCtr, RXByteCtr;
uint16_t *rxbufptr;
//volatile uint8_t flag, rx;
int8_t who;

void initClocks(void);
void initPorts(void);
void initBoard(void);
void populateNVIC(void);

int main(void)
    {
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    initBoard();
    __enable_interrupts();

    while(1){
        who = I2C_ReadRegister(FXOS_I2C_ADDR, FXOS_WHO_AM_I);
        for(i=0;i<12000;i++); //wait 10ms@12MHz
    }
}

void initBoard(void)
{
    initPorts();
    initClocks();
    initI2C();
    populateNVIC();
}

void initClocks(void)
{
    CS->KEY = CS_KEY_VAL;
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;     // Select ACLK = REFO, SMCLK = MCLK = DCO (12MHz currently)
    CS->KEY = 0;
}

void populateNVIC(void)
{
    //This function exists to populate the Nested Vector Interrupt Controller with proper IRQ enable bits
    //These bits must be set along with peripheral interrupt bits for IRQs to trigger properly.

    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31); //eUSCI_B0 Interrupt Set Enable Bit
}

void initPorts(void)
{
    //Initializes MSP-EXP432P401R board to lowest power consumption state.
    //For portability, any additional port mapping should be performed in separate functions after this is executed.

    P1OUT = 0x00;
    P1DIR |= BIT7|BIT6|BIT5|BIT3|BIT2|BIT0;

    P2OUT = 0x00;
    P2DIR |= BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0;

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

