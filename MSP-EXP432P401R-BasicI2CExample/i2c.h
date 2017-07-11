/*
 * i2c.h
 *
 *  Created on: Jun 5, 2017
 *      Author: Eric
 */

#ifndef I2C_H_
#define I2C_H_

#include <msp.h>

void I2C_ReadMultipleRegisters(uint8_t addr, uint8_t regbase, uint8_t rxbytes);
uint8_t I2C_ReadRegister(uint8_t addr, uint8_t reg);
void I2C_WriteRegister(uint8_t addr, uint8_t reg, uint8_t data);
void initI2C(void);



#endif /* I2C_H_ */
