#include <msp.h>
#include "stdlib.h"
#include "stdio.h"
#include "BCUART.h"
#include "servo.h"

extern int temp;

void PORT1_IRQHandler(void)
{
    if(P1IFG & BIT1)
    {
//        P1OUT ^= BIT0; //Disabled blink
        P1IFG &= ~BIT1; //Clear interrupt
        TIMER_A0->CCR[1] = 3620;
    }
    else if(P1IFG & BIT4)
    {
//        P1OUT ^= BIT0; //Disabled blink
        P1IFG &= ~BIT4; //Clear interrupt
        TIMER_A0->CCR[1] = 1040;

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
        if(RXchar == 'p')
        {
            TIMER_A0->CCR[1] = TIMER_A0->CCR[1] + 5;
        } else if(RXchar == 'o')
        {
            TIMER_A0->CCR[1] = TIMER_A0->CCR[1] - 5;
        }
        //        P2OUT ^= BIT2; Disabled LED toggle for showing data XFER
    }

}

void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P2OUT ^= BIT1; //Disabled blink
}
