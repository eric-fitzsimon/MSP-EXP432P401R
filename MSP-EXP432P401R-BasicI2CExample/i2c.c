#include "i2c.h"

extern uint8_t txbufctr, rxbufctr;
extern uint8_t rxbuf[], txbuf[];
extern uint8_t TXByteCtr, RXByteCtr;
extern volatile uint8_t flag, rx;

void initI2C(void)
{
    P1SEL0 |= BIT6|BIT7; //Enable peripheral pins
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST + EUSCI_B_CTLW0_SSEL__SMCLK + EUSCI_B_CTLW0_MODE_3 + EUSCI_B_CTLW0_MST + EUSCI_B_CTLW0_SYNC; //Use SMCLK, stay in reset
    EUSCI_B0->BRW = 30; //12,000,000(Hz)/100,000(Hz) = 120.................12M/400K = 30 for 400kHz operation, 60 for 200kHz, 120 for 100kHz
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Take eUSCI out of reset
}

void I2C_WriteRegister(uint8_t addr, uint8_t reg, uint8_t data)
{
    //I2C Polling Write Register function with no error checking
    //(single byte write register address, single byte write register data)
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST + EUSCI_B_CTLW0_SSEL__SMCLK + EUSCI_B_CTLW0_MODE_3 + EUSCI_B_CTLW0_MST + EUSCI_B_CTLW0_SYNC; //Use SMCLK, stay in reset
    EUSCI_B0->BRW = 30; //12,000,000(Hz)/100,000(Hz) = 120.................12M/400K = 30 for 400kHz operation, 60 for 200kHz
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Initialize eUSCI

    EUSCI_B0->I2CSA = addr; //Set slave address in module
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR | EUSCI_B_CTLW0_TXSTT; //Set eUSCI module to transmit mode and send start condition
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG)); //Wait for TXIFG, indicating data is ready to be sent to TXBUFFER
    EUSCI_B0->TXBUF = reg; //Write data to TXBUF
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG)); //Wait for TXIFG, indicating data has been shifted out
    EUSCI_B0->TXBUF = data; //Write data to TXBUF
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG)); //Wait for TXIFG, indicating data has been shifted out
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP; //Send stop condition to module while transmitting final byte
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent
    EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG; //Clear TXIFG on exit
}

uint8_t I2C_ReadRegister(uint8_t addr, uint8_t reg)
{
    //I2C Polling Read Register function with no error checking
    //(single byte write, repeated start, single byte read)

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST + EUSCI_B_CTLW0_SSEL__SMCLK + EUSCI_B_CTLW0_MODE_3 + EUSCI_B_CTLW0_MST + EUSCI_B_CTLW0_SYNC; //Use SMCLK, stay in reset
    EUSCI_B0->BRW = 30; //12,000,000(Hz)/100,000(Hz) = 120.................12M/400K = 30 for 400kHz operation, 60 for 200kHz
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Initialize eUSCI

    EUSCI_B0->I2CSA = addr;     //Set slave address in module
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent for transmission
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR | EUSCI_B_CTLW0_TXSTT; //Set EUSCI_B0 to transmit mode and send start condition
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));
    EUSCI_B0->TXBUF = reg;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR; //Switch to I2C RX Mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; // Repeated start condition
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTT); //wait for Repeated start condition
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP; //Begin Stop Transmission while receiving byte
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG)); //Wait for RX
    rxbuf[0] = EUSCI_B0->RXBUF; //Receive to Buffer
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent
    EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG; //Clear TXIFG on exit
    return rxbuf[0];
}

void I2C_ReadMultipleRegisters(uint8_t addr, uint8_t regbase, uint8_t rxbytes)
{
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST + EUSCI_B_CTLW0_SSEL__SMCLK + EUSCI_B_CTLW0_MODE_3 + EUSCI_B_CTLW0_MST + EUSCI_B_CTLW0_SYNC; //Use SMCLK, stay in reset
    EUSCI_B0->BRW = 30; //12,000,000(Hz)/100,000(Hz) = 120.................12M/400K = 30 for 400kHz operation, 60 for 200kHz
    EUSCI_B0->CTLW1 |= EUSCI_B_CTLW1_ASTP_2;// Automatic stop generated after EUSCI_B0->TBCNT is reached
    EUSCI_B0->TBCNT = rxbytes;
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_B0->IE |= EUSCI_B_IE_TXIE | EUSCI_B_IE_RXIE | EUSCI_B_IE_NACKIE;// | EUSCI_B_IE_BCNTIE; // Enable TX, RX, and NACK interrupts
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent
    EUSCI_B0->I2CSA = addr;

    txbufctr = rxbufctr = 0;
    TXByteCtr = 1;
    RXByteCtr = rxbytes;
    txbuf[0] = regbase;

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR | EUSCI_B_CTLW0_TXSTT; //I2C TX and start condition
    while(TXByteCtr);
    while(RXByteCtr);
    while(EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP); //Ensure stop condition has been sent
}
