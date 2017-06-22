#include <msp.h>
#include "stdlib.h"
#include "stdio.h"
#include "BCUART.h"

void sendBCByte(uint8_t byte)
{
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); //Check if TXBUF is empty
    EUSCI_A0->TXBUF = byte; //Echo back character from RXBUF

}

void sendBCBytes(uint8_t *ptr, uint8_t bytes)
{
    uint8_t i=0;
    for(i=0;i<bytes;i++)
    {
        sendBCByte(ptr[i]);
    }
}

//Helper function to send string of character to Backchannel UART
void sendBCString(uint8_t *string)
{
    uint16_t i=0;
    for(i=0;i<strlen(string);i++)
    {
        sendBCByte(string[i]);
    }
}

void DateString(void)
{
    //Needs cleaning up/output formatting
    char DS[30];
    char temp[6];
    memset(DS, 0, sizeof(DS));
    sprintf(DS, "%02X", RTCYEAR);
    sprintf(temp, "%02X", RTCDATE);
    strcat(DS,temp); memset(temp, 0, sizeof(temp)); strcat(DS,"-");
    sprintf(temp, "%X", RTCHOUR);
    strcat(DS,temp); memset(temp, 0, sizeof(temp));
    sprintf(temp, "%X", RTCMIN);
    strcat(DS,temp); memset(temp, 0, sizeof(temp));
    sprintf(temp, "%X", RTCSEC);
    strcat(DS,temp); memset(temp, 0, sizeof(temp));
    strcat(DS,"\n\r");
    sendBCString(DS);
}
