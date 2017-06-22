/*
 * BCUART.h
 *
 *  Created on: May 11, 2017
 *      Author: Eric
 */

#ifndef BCUART_H_
#define BCUART_H_

void sendBCByte(uint8_t byte);
void sendBCString(uint8_t *string);
void DateString(void);
void sendBCBytes(uint8_t *ptr, uint8_t bytes);



#endif /* BCUART_H_ */
