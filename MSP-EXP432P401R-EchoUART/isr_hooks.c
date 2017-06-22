#include <msp.h>

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
    }
}

void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); //Check if TXBUF is empty
        EUSCI_A0->TXBUF = EUSCI_A0->RXBUF; //Echo back character from RXBUF
    }

}
