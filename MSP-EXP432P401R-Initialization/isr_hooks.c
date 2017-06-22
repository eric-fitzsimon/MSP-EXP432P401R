#include <msp.h>


//Basic IRQ for PORT1 to check for button press on P1.1 or P1.4. No debounce implemented.
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
