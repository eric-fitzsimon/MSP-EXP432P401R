#include <msp.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "FXOS8700.h"

void EUSCIB0_IRQHandler(void)
{
    extern uint8_t txbufctr, rxbufctr;
    extern uint8_t rxbuf[15], txbuf[5];
    extern uint8_t TXByteCtr, RXByteCtr;

    if (EUSCI_B0->IFG & EUSCI_B_IFG_NACKIFG) //NACK Flag
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_NACKIFG;         //Clear NACK Flag
        EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; // Send start condition
    }
    if (EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG)  //Receive Flag
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG;
        if(RXByteCtr)
        {
            rxbuf[rxbufctr] = EUSCI_B0->RXBUF;
            RXByteCtr--;
            rxbufctr++;
        }
    }
    if (EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG) //Transmit Flag
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG;
        if(TXByteCtr)
        {
            EUSCI_B0->TXBUF = txbuf[txbufctr];
            TXByteCtr--;
            txbufctr++;
        } else {
                EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR; //I2C RX Mode
                EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; // Start condition
        }
    }
    if (EUSCI_B0->IFG & EUSCI_B_IFG_BCNTIFG) //Terminal Byte Count Flag
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_BCNTIFG;
    }
}
