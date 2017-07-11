/*
 *  FXOS8700.c
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Very basic I2C driver for FXOS8700 accelerometer+magnetometer.
 *
 *  Notes:
 *      Initially written for Texas Instruments MSP-EXP432P401R Development Board
 *      Assumes I2C functions exist as below:
 *           void I2C_ReadMultipleRegisters(uint8_t addr, uint8_t regbase, uint8_t rxbytes);
 *           uint8_t I2C_ReadRegister(uint8_t addr, uint8_t reg);
 *           void I2C_WriteRegister(uint8_t addr, uint8_t reg, uint8_t data);
 *      Assumes I2C receive buffer exists somewhere (rxbuf)
 *      Provides no error checking
 */

#include "FXOS8700.h"
#include "i2c.h"

extern uint8_t rxbuf[];

void FXOS_AutoInit(void)
{
    uint8_t zcomp;
    //Check if FXOS8700 exists
    if(I2C_ReadRegister(FXOS_I2C_ADDR, FXOS_WHO_AM_I) == FXOS_IDENTITY)
    {
        //Enable accelerometer and magnetometer with magnetometer auto calibration and maximum oversampling
        //Enable hybrid mode with auto-increment for single-burst read
        //Put device in active mode with noise reduction and 25Hz update
        //Enable high resolution accelerometer mode
        zcomp = I2C_ReadRegister(FXOS_I2C_ADDR, FXOS_PL_BF_ZCOMP);
        I2C_WriteRegister(FXOS_I2C_ADDR, FXOS_M_CTRL_REG1, (FXOS_M_CTRL_REG1_HMS_2 | FXOS_M_CTRL_REG1_ACAL | FXOS_M_CTRL_REG1_OS0 |FXOS_M_CTRL_REG1_OS1 |FXOS_M_CTRL_REG1_OS2)); //Enable auto calibration, accelerometer, and magnetometer
        I2C_WriteRegister(FXOS_I2C_ADDR, FXOS_M_CTRL_REG2, (FXOS_M_CTRL_REG2_HYBAUTOINC)); //Enable hybrid mode. Both accel and magnetometer data can be read in single burst.
        I2C_WriteRegister(FXOS_I2C_ADDR, FXOS_CTRL_REG1, (FXOS_CTRL_REG1_LNOISE | FXOS_CTRL_REG1_ACTIVE | FXOS_CTRL_REG1_DR2)); //Put device in active mode, enable noise reduction, 25Hz Update Hybrid Mode.
        I2C_WriteRegister(FXOS_I2C_ADDR, FXOS_CTRL_REG2, (FXOS_CTRL_REG2_MODS1)); //Enable high resolution accelerometer mode
    } else
    {
        while(1); //loop forever to catch error
    }
}

void FXOS_Update(FXOSDATA *acceldata)
{
    I2C_ReadMultipleRegisters(FXOS_I2C_ADDR, 0x00, 13);
    if(rxbuf[0] & FXOS_DR_STATUS_ZYXDR)
    {
    acceldata->ax =  (int16_t) (((rxbuf[1] << 8) | rxbuf[2])) >> 2;
    acceldata->ay = (int16_t) (((rxbuf[3] << 8) | rxbuf[4])) >> 2;
    acceldata->az = (int16_t) (((rxbuf[5] << 8) | rxbuf[6])) >> 2;
    acceldata->mx =  (int16_t) ((rxbuf[7] << 8) | rxbuf[8]);
    acceldata->my = (int16_t) ((rxbuf[9] << 8) | rxbuf[10]);
    acceldata->mz = (int16_t) ((rxbuf[11] << 8) | rxbuf[12]);
    rxbuf[0] = 0x00;
    }
}

uint8_t FXOS_Probe(uint8_t FXOS_ADDR)
{
return 1;
}

uint8_t FXOS_Reset(void)
{
return 1;
}

