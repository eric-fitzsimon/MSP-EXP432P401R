/*
 *  main.c
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Project that performs basic initializations and demonstrates basic control of an SG90 servo via PWM output from TIMER_A0 module.
 *  On input from user ('o' or 'p' from BCUART), duty cycle is altered to move servo.
 *
 *  Notes:
 *      No debounce implemented on button press.
 *      Servo duty cycle is affected by user input from BCUART (see EUSCI_A0 ISR).
 *      No error checking.
 *
 *
 */
#include <msp.h>
#include "msp_compatibility.h"
#include "stdio.h"

void initClocks(void);
void initPorts(void);
void populateNVIC(void);
void initBCUART(void);
void initTimerAPWM(void);
void initRTC(void);

volatile int temp = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    initClocks();
    initPorts();
    populateNVIC();
    initBCUART();
    initTimerAPWM();
    initRTC();

    __enable_interrupts();

    while(1)
    {
        __sleep();
    }
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

    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31); //Port_1 Interrupt Set Enable Bit
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); //eUSCI_A0 Interrupt Set Enable Bit
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31); //Timer_A0 Interrupt Set Enable Bit
}

void initRTC(void)
{
    // Configure RTC
      // Unlock RTC key protected registers
      // RTC enable, BCD mode, RTC hold
      // enable RTC read ready interrupt
      // enable RTC time event interrupt
      // set time event interrupt to trigger when minute changes
      RTC_C->CTL0 = RTC_C_KEY;// | RTC_C_CTL0_TEVIE; Turn off Time Event Interrupt
      RTC_C->CTL13 = RTC_C_CTL13_HOLD | RTC_C_CTL13_MODE | RTC_C_CTL13_BCD;// | RTC_C_CTL13_TEV_0; Time Event Interrupt for minute changing

      RTC_C->YEAR = 0x2017;                   // Year = 0x2016
      RTC_C->DATE = (0x05 << RTC_C_DATE_MON_OFS) | (0x08 | RTC_C_DATE_DAY_OFS); // Month = 0x04 = April // Day = 0x05 = 5th
      RTC_C->TIM1 = (0x01 << RTC_C_TIM1_DOW_OFS) |(0x14 << RTC_C_TIM1_HOUR_OFS); // Day of week = 0x01 = Monday // Hour = 0x10
      RTC_C->TIM0 = (0x35 << RTC_C_TIM0_MIN_OFS) |(0x01 << RTC_C_TIM0_SEC_OFS); // Minute = 0x32 // Seconds = 0x45
      RTC_C->CTL13 = RTC_C->CTL13 & ~(RTC_C_CTL13_HOLD);      // Start RTC calendar mode
      RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);      // Lock the RTC registers

}

void initTimerAPWM(void)
{
    P2SEL0 |= BIT4|BIT6; //Enable
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7; //Set/reset bit for P2.4, toggles bit off/on at terminal count of CCR1
    TIMER_A0->CCTL[3] |= TIMER_A_CCTLN_OUTMOD_7; //Set/reset bit for P2.6, toggles bit off/on at terminal count of CCR3
    TIMER_A0->CCR[0] = 30000; //32768/50 = 655 = ~50Hz period
    TIMER_A0->CCR[1] = 0; //655/2 = 326 = 50% Duty Cycle
    TIMER_A0->CCR[3] = 0; //655/4 = 25% Duty Cycle
    TIMER_A0->CTL |= TASSEL_2 | ID_3 | MC_1; //SMCLK source, SMCLK/8 divider, Up Mode -----> This config starts timer
}

void initBCUART(void)
{
    P1SEL0 |= BIT3|BIT2; //Enable peripheral pins
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; //Put eUSCI_A0 in reset state
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST | EUSCI_A_CTLW0_SSEL__SMCLK; //Use SMCLK, stay in reset
    EUSCI_A0->BRW = 78;                     // 3,000,000/16/9600 = 20
    EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16; //Oversampling mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt
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
