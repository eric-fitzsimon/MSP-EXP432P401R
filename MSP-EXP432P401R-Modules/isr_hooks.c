#include <msp.h>
#include "stdlib.h"
#include "stdio.h"
#include "BCUART.h"

extern int temp;

void PORT1_IRQHandler(void)
{
    if(P1IFG & BIT1)
    {
//        P1OUT ^= BIT0; //Disabled blink
        P1IFG &= ~BIT1; //Clear interrupt
    }
    else if(P1IFG & BIT4)
    {
//        P1OUT ^= BIT0; //Disabled blink
        P1IFG &= ~BIT4; //Clear interrupt
//        DateString(); //Disabled function to print timestamp
    }
}

void EUSCIA0_IRQHandler(void)
{
    uint8_t RXchar;
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        RXchar = EUSCI_A0-> RXBUF;
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); //Check if TXBUF is empty
        EUSCI_A0->TXBUF = RXchar; //Echo back character from RXBUF
        if(RXchar == 'a')
        {
            DateString(); //Print timestamp when 'a' is received via UART
        } else if(RXchar == 't')
        {
         //Enable ADC14 conversion here
            ADC14->CTL0 |= ADC14_CTL0_SC;       // Sampling and conversion start
            while(ADC14->CTL0 & ADC14_CTL0_SC);
            sendBCBytes(temp,4);
            sendBCString("\r\n");
        }
//        P2OUT ^= BIT2; Disabled LED toggle for showing data XFER
    }
}

void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
//    P2OUT ^= BIT1; //Disabled blink
}

void ADC14_IRQHandler(void)
{
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG0)
    {
        temp = ADC14->MEM[0];
    }
    ADC14->CTL0 &= ~ADC14_CTL0_SC;       // Sampling and conversion stop
}
