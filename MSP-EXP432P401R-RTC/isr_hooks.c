#include <msp.h>
#include "stdlib.h"
#include "stdio.h"

void PORT1_IRQHandler(void)
{
    if(P1IFG & BIT1)
    {
        P1OUT ^= BIT0;
        P1IFG &= ~BIT1;
    }
    else if(P1IFG & BIT4)
    {
        P1OUT ^= BIT0;
        P1IFG &= ~BIT4;
        DateString();
    }
}


void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); //Check if TXBUF is empty
        EUSCI_A0->TXBUF = EUSCI_A0->RXBUF; //Echo back character from RXBUF
        P2OUT ^= BIT2;
    }

}

void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P2OUT ^= BIT1;
    //    TIMER_A0->CTL = TAIFG;
}
