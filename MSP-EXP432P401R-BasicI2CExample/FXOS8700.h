/*
 * FXOS8700.h
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Description: Header for basic FXOS8700 driver.
 *  Version: 0.1
 *
 *  Notes:
 *      Still missing many register bit definitions
 */
#ifndef FXOS8700_H_
#define FXOS8700_H_

#include <msp.h>
#include "math.h"

typedef struct {
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t mx;
    int16_t my;
    int16_t mz;
    float axyz;
    float mxyz;
    float heading;
    float xangle;
    float yangle;
    float zangle;
    float xrads;
    float yrads;
    float zrads;
} FXOSDATA; //Structure for FXOS8700 output and calculated data

void FXOS_Update(FXOSDATA *acceldata);
void FXOS_AutoInit(void);

#define FXOS_I2C_ADDR                   (uint8_t)(0x1F) //Address of FXOS8700 on I2C bus
#define FXOS_IDENTITY                      (uint8_t)(0xC7) //Expected Identity at I2C address

#define FXOS_ACCEL_LSB_2G   0.244f /* Accelerometer mg/LSB in 2G mode */
#define FXOS_ACCEL_LSB_4G   0.488f /* Accelerometer mg/LSB in 4G mode */
#define FXOS_ACCEL_LSB_8G   0.976f /* Accelerometer mg/LSB in 8G mode */
#define FXOS_MAG_LSB        0.1f /* Magnetometer uT/LSB */
#define PI                  3.141593f

/* FXOS8700 Registers */
#define FXOS_STATUS_REG                 (uint8_t)(0x00) /* Alias for DR_STATUS or F_STATUS */
#define FXOS_OUT_X_MSB                  (uint8_t)(0x01) /* 8 MSBs of 14-bit X-axis accelerometer sample */
#define FXOS_OUT_X_LSB                  (uint8_t)(0x02) /* 6 MSBs of 14-bit X-axis accelerometer sample */
#define FXOS_OUT_Y_MSB                  (uint8_t)(0x03) /* 8 MSBs of 14-bit Y-axis accelerometer sample */
#define FXOS_OUT_Y_LSB                  (uint8_t)(0x04) /* 6 MSBs of 14-bit Y-axis accelerometer sample */
#define FXOS_OUT_Z_MSB                  (uint8_t)(0x05) /* 8 MSBs of 14-bit Z-axis accelerometer sample */
#define FXOS_OUT_Z_LSB                  (uint8_t)(0x06) /* 6 MSBs of 14-bit Z-axis accelerometer sample */
#define FXOS_F_SETUP                    (uint8_t)(0x09) /* FIFO Setup */
#define FXOS_TRIG_CFG                   (uint8_t)(0x0A) /* FIFO event trigger configuration register */
#define FXOS_SYSMOD                     (uint8_t)(0x0B) /* Current System mode */
#define FXOS_INT_SOURCE                 (uint8_t)(0x0C) /* Interrupt Status */
#define FXOS_WHO_AM_I                   (uint8_t)(0x0D) /* Device ID */
#define FXOS_XYZ_DATA_CFG               (uint8_t)(0x0E) /* Acceleration Dynamic Range and filter enable */
#define FXOS_HP_FILTER_CUTOFF           (uint8_t)(0x0F) /* Pulse Detection HPF/LPF Enable and cutoff */
#define FXOS_PL_STATUS                  (uint8_t)(0x10) /* Landscape/Portrait Orientation Status */
#define FXOS_PL_CFG                     (uint8_t)(0x11) /* Landscape/Portrait Configuration */
#define FXOS_PL_COUNT                   (uint8_t)(0x12) /* Landscape/Portrait Debounce Counter */
#define FXOS_PL_BF_ZCOMP                (uint8_t)(0x13) /* Back/Front trip angle threshold */
#define FXOS_PL_THS_REG                 (uint8_t)(0x14) /* Portrait to Landscape trip threshold angle and hysteresis */
#define FXOS_A_FFMT_CFG                 (uint8_t)(0x15) /* Freefall/Motion Function Configuration */
#define FXOS_A_FFMT_SRC                 (uint8_t)(0x16) /* Freefall/Motion Event Source Register */
#define FXOS_A_FFMT_THS                 (uint8_t)(0x17) /* Freefall/Motion Threshold Register */
#define FXOS_FFMT_COUNT                 (uint8_t)(0x18) /* Freefall/Motion Debounce Counter */
#define FXOS_TRANSIENT_CFG              (uint8_t)(0x1D) /* FIFO Setup */
#define FXOS_TRANSIENT_SRC              (uint8_t)(0x1E) /* Transient Event Status Register */
#define FXOS_TRANSIENT_THS              (uint8_t)(0x1F) /* Transient Event Threshold */
#define FXOS_TRANSIENT_COUNT            (uint8_t)(0x20) /* Transient Debounce Counter */
#define FXOS_PULSE_CFG                  (uint8_t)(0x21) /* Pulse Function Configuration */
#define FXOS_PULSE_SRC                  (uint8_t)(0x22) /* Pulse Function Source Register */
#define FXOS_PULSE_THSX                 (uint8_t)(0x23) /* X-axis pulse threshold */
#define FXOS_PULSE_THSY                 (uint8_t)(0x24) /* Y-axis pulse threshold */
#define FXOS_PULSE_THSZ                 (uint8_t)(0x25) /* Z-axis pulse threshold */
#define FXOS_PULSE_TMLT                 (uint8_t)(0x26) /* Time limit for pulse detection */
#define FXOS_PULSE_LTCY                 (uint8_t)(0x27) /* Latency time for second pulse detection */
#define FXOS_PULSE_WIND                 (uint8_t)(0x28) /* Window time for second pulse detection */
#define FXOS_ASLP_COUNT                 (uint8_t)(0x29) /* Inactivity counter setting for auto-sleep */
#define FXOS_CTRL_REG1                  (uint8_t)(0x2A) /* System ODR, Accelerometer OSR, operating Mode */
#define FXOS_CTRL_REG2                  (uint8_t)(0x2B) /* Self-test, reset, accelerometer OSR, and sleep mode */
#define FXOS_CTRL_REG3                  (uint8_t)(0x2C) /* Sleep mode interrupt wake enable, interrupt polarity */
#define FXOS_CTRL_REG4                  (uint8_t)(0x2D) /* Interrupt Enable Register */
#define FXOS_CTRL_REG5                  (uint8_t)(0x2E) /* Interrupt pin (INT1/INT2) mapping */
#define FXOS_OFF_X                      (uint8_t)(0x2F) /* X-axis accelerometer offset adjustment */
#define FXOS_OFF_Y                      (uint8_t)(0x30) /* Y-axis accelerometer offset adjustment */
#define FXOS_OFF_Z                      (uint8_t)(0x31) /* Z-axis accelerometer offset adjustment */
#define FXOS_M_DR_STATUS                (uint8_t)(0x32) /* Magnetic Data ready */
#define FXOS_M_OUT_X_MSB                (uint8_t)(0x33) /* MSBs of 16-bit X-axis Magnetic Data */
#define FXOS_M_OUT_X_LSB                (uint8_t)(0x34) /* LSBs of 16-bit X-axis Magnetic Data */
#define FXOS_M_OUT_Y_MSB                (uint8_t)(0x35) /* MSBs of 16-bit Y-axis Magnetic Data */
#define FXOS_M_OUT_Y_LSB                (uint8_t)(0x36) /* LSBs of 16-bit Y-axis Magnetic Data */
#define FXOS_M_OUT_Z_MSB                (uint8_t)(0x37) /* MSBs of 16-bit Z-axis Magnetic Data */
#define FXOS_M_OUT_Z_LSB                (uint8_t)(0x38) /* LSBs of 16-bit Z-axis Magnetic Data */
#define FXOS_CMP_X_MSB                  (uint8_t)(0x39) /* Bits[13:8] of integrated X-axis acceleration data */
#define FXOS_CMP_X_LSB                  (uint8_t)(0x3A) /* Bits[7:0] of integrated X-axis acceleration data */
#define FXOS_CMP_Y_MSB                  (uint8_t)(0x3B) /* Bits[13:8] of integrated Y-axis acceleration data */
#define FXOS_CMP_Y_LSB                  (uint8_t)(0x3C) /* Bits[7:0] of integrated Y-axis acceleration data */
#define FXOS_CMP_Z_MSB                  (uint8_t)(0x3D) /* Bits[13:8] of integrated Z-axis acceleration data */
#define FXOS_CMP_Z_LSB                  (uint8_t)(0x3E) /* Bits[7:0] of integrated Z-axis acceleration data */
#define FXOS_M_OFF_X_MSB                (uint8_t)(0x3F) /* MSB of magnetometer of X-axis offset */
#define FXOS_M_OFF_X_LSB                (uint8_t)(0x40) /* LSB of magnetometer of X-axis offset */
#define FXOS_M_OFF_Y_MSB                (uint8_t)(0x41) /* MSB of magnetometer of Y-axis offset */
#define FXOS_M_OFF_Y_LSB                (uint8_t)(0x42) /* LSB of magnetometer of Y-axis offset */
#define FXOS_M_OFF_Z_MSB                (uint8_t)(0x43) /* MSB of magnetometer of Z-axis offset */
#define FXOS_M_OFF_Z_LSB                (uint8_t)(0x44) /* LSB of magnetometer of Z-axis offset */
#define FXOS_MAX_X_MSB                  (uint8_t)(0x45) /* Magnetometer X-axis Maximum value MSB */
#define FXOS_MAX_X_LSB                  (uint8_t)(0x46) /* Magnetometer X-axis Maximum value LSB */
#define FXOS_MAX_Y_MSB                  (uint8_t)(0x47) /* Magnetometer Y-axis Maximum value MSB */
#define FXOS_MAX_Y_LSB                  (uint8_t)(0x48) /* Magnetometer Y-axis Maximum value LSB */
#define FXOS_MAX_Z_MSB                  (uint8_t)(0x49) /* Magnetometer Z-axis Maximum value MSB */
#define FXOS_MAX_Z_LSB                  (uint8_t)(0x4A) /* Magnetometer Z-axis Maximum value LSB */
#define FXOS_MIN_X_MSB                  (uint8_t)(0x4B) /* Magnetometer X-axis Minimum Value MSB */
#define FXOS_MIN_X_LSB                  (uint8_t)(0x4C) /* Magnetometer X-axis Minimum Value LSB */
#define FXOS_MIN_Y_MSB                  (uint8_t)(0x4D) /* Magnetometer Y-axis Minimum Value MSB */
#define FXOS_MIN_Y_LSB                  (uint8_t)(0x4E) /* Magnetometer Y-axis Minimum Value LSB */
#define FXOS_MIN_Z_MSB                  (uint8_t)(0x4F) /* Magnetometer Z-axis Minimum Value MSB */
#define FXOS_MIN_Z_LSB                  (uint8_t)(0x50) /* Magnetometer Z-axis Minimum Value LSB */
#define FXOS_TEMP                       (uint8_t)(0x51) /* Device Temperature (-128-127 degrees C) */
#define FXOS_M_THS_CFG                  (uint8_t)(0x52) /* Magnetic threshold detection function configuration */
#define FXOS_M_THS_SRC                  (uint8_t)(0x53) /* Magnetic threshold event source register */
#define FXOS_M_THS_X_MSB                (uint8_t)(0x54) /* X-axis magnetic threshold MSB */
#define FXOS_M_THS_X_LSB                (uint8_t)(0x55) /* X-axis magnetic threshold LSB */
#define FXOS_M_THS_Y_MSB                (uint8_t)(0x56) /* Y-axis magnetic threshold MSB */
#define FXOS_M_THS_Y_LSB                (uint8_t)(0x57) /* Y-axis magnetic threshold LSB */
#define FXOS_M_THS_Z_MSB                (uint8_t)(0x58) /* Z-axis magnetic threshold MSB */
#define FXOS_M_THS_Z_LSB                (uint8_t)(0x59) /* Z-axis magnetic threshold LSB */
#define FXOS_M_THS_COUNT                (uint8_t)(0x5A) /* Magnetic Threshold debounce counter */
#define FXOS_M_CTRL_REG1                (uint8_t)(0x5B) /* Control for magnetic sensor functions */
#define FXOS_M_CTRL_REG2                (uint8_t)(0x5C) /* Control for magnetic sensor functions */
#define FXOS_M_CTRL_REG3                (uint8_t)(0x5D) /* Control for magnetic sensor functions */
#define FXOS_M_INT_SRC                  (uint8_t)(0x5E) /* Magnetic interrupt source */
#define FXOS_A_VECM_CFG                 (uint8_t)(0x5F) /* Acceleration vector-magnitude configuration register */
#define FXOS_A_VECM_THS_MSB             (uint8_t)(0x60) /* Acceleration vector-magnitude threshold MSB */
#define FXOS_A_VECM_THS_LSB             (uint8_t)(0x61) /* Acceleration vector-magnitude threshold LSB */
#define FXOS_A_VECM_CNT                 (uint8_t)(0x62) /* Acceleration vector-magnitude debounce count */
#define FXOS_A_VECM_INITX_MSB           (uint8_t)(0x63) /* Acceleration vector-magnitude X-axis Reference Value MSB */
#define FXOS_A_VECM_INITX_LSB           (uint8_t)(0x64) /* Acceleration vector-magnitude X-axis Reference Value LSB */
#define FXOS_A_VECM_INITY_MSB           (uint8_t)(0x65) /* Acceleration vector-magnitude Y-axis Reference Value MSB */
#define FXOS_A_VECM_INITY_LSB           (uint8_t)(0x66) /* Acceleration vector-magnitude Y-axis Reference Value LSB */
#define FXOS_A_VECM_INITZ_MSB           (uint8_t)(0x67) /* Acceleration vector-magnitude Z-axis Reference Value MSB */
#define FXOS_A_VECM_INITZ_LSB           (uint8_t)(0x68) /* Acceleration vector-magnitude Z-axis Reference Value LSB */
#define FXOS_M_VECM_CFG                 (uint8_t)(0x69) /* Magnetic Vector-Magnitude configuration register */
#define FXOS_M_VECM_THS_MSB             (uint8_t)(0x6A) /* Magnetic Vector-Magnitude threshold MSB */
#define FXOS_M_VECM_THS_LSB             (uint8_t)(0x6B) /* Magnetic Vector-Magnitude threshold LSB */
#define FXOS_M_VECM_CNT                 (uint8_t)(0x6C) /* Magnetic Vector-Magnitude debounce count */
#define FXOS_M_VECM_INITX_MSB           (uint8_t)(0x6D) /* Magnetic Vector-Magnitude reference value X-axis MSB */
#define FXOS_M_VECM_INITX_LSB           (uint8_t)(0x6E) /* Magnetic Vector-Magnitude reference value X-axis LSB */
#define FXOS_M_VECM_INITY_MSB           (uint8_t)(0x6F) /* Magnetic Vector-Magnitude reference value Y-axis MSB */
#define FXOS_M_VECM_INITY_LSB           (uint8_t)(0x70) /* Magnetic Vector-Magnitude reference value Y-axis LSB */
#define FXOS_M_VECM_INITZ_MSB           (uint8_t)(0x71) /* Magnetic Vector-Magnitude reference value Z-axis MSB */
#define FXOS_M_VECM_INITZ_LSB           (uint8_t)(0x72) /* Magnetic Vector-Magnitude reference value Z-axis LSB */
#define FXOS_A_FFMT_THS_X_MSB           (uint8_t)(0x73) /* X-axis FFMT threshold MSB */
#define FXOS_A_FFMT_THS_X_LSB           (uint8_t)(0x74) /* X-axis FFMT threshold LSB */
#define FXOS_A_FFMT_THS_Y_MSB           (uint8_t)(0x75) /* Y-axis FFMT threshold MSB */
#define FXOS_A_FFMT_THS_Y_LSB           (uint8_t)(0x76) /* Y-axis FFMT threshold LSB */
#define FXOS_A_FFMT_THS_Z_MSB           (uint8_t)(0x77) /* Z-axis FFMT threshold MSB */
#define FXOS_A_FFMT_THS_Z_LSB           (uint8_t)(0x78) /* Z-axis FFMT threshold LSB */

/* FXOS_DR_STATUS Bits (Register 0x00) */
#define FXOS_DR_STATUS_XDR                      (uint8_t)(0x01) /* X-axis data ready bit */
#define FXOS_DR_STATUS_YDR                      (uint8_t)(0x02) /* Y-axis data ready bit */
#define FXOS_DR_STATUS_ZDR                      (uint8_t)(0x04) /* Z-axis data ready bit */
#define FXOS_DR_STATUS_ZYXDR                    (uint8_t)(0x08) /* XYZ-axes data ready bit */
#define FXOS_DR_STATUS_XOW                      (uint8_t)(0x10) /* X-axis data overwritten bit */
#define FXOS_DR_STATUS_YOW                      (uint8_t)(0x20) /* Y-axis data overwritten bit */
#define FXOS_DR_STATUS_ZOW                      (uint8_t)(0x40) /* Z-axis data overwritten bit */
#define FXOS_DR_STATUS_ZYXOW                    (uint8_t)(0x80) /* XYZ-axes data overwritten bit */

/* FXOS_F_STATUS Bits (Register 0x00)*/

#define FXOS_F_STATUS_F_CNT0                    (uint8_t)(0x01) /* FIFO Sample counter bit 0 */
#define FXOS_F_STATUS_F_CNT1                    (uint8_t)(0x02) /* FIFO Sample counter bit 1 */
#define FXOS_F_STATUS_F_CNT2                    (uint8_t)(0x04) /* FIFO Sample counter bit 2 */
#define FXOS_F_STATUS_F_CNT3                    (uint8_t)(0x08) /* FIFO Sample counter bit 3 */
#define FXOS_F_STATUS_F_CNT4                    (uint8_t)(0x10) /* FIFO Sample counter bit 4 */
#define FXOS_F_STATUS_F_CNT5                    (uint8_t)(0x20) /* FIFO Sample counter bit 5 */
#define FXOS_F_STATUS_F_WMKF                    (uint8_t)(0x40) /* FIFO Watermark flag */
#define FXOS_F_STATUS_F_OVF                     (uint8_t)(0x80) /* FIFO overflow flag */

/* FXOS_F_SETUP Bits (0x09) */

#define FXOS_F_SETUP_F_WMRK0                    (uint8_t)(0x01) /* FIFO Sample Count Watermark Setting Bit 0 */
#define FXOS_F_SETUP_F_WMRK1                    (uint8_t)(0x02) /* FIFO Sample Count Watermark Setting Bit 1 */
#define FXOS_F_SETUP_F_WMRK2                    (uint8_t)(0x04) /* FIFO Sample Count Watermark Setting Bit 2 */
#define FXOS_F_SETUP_F_WMRK3                    (uint8_t)(0x08) /* FIFO Sample Count Watermark Setting Bit 3 */
#define FXOS_F_SETUP_F_WMRK4                    (uint8_t)(0x10) /* FIFO Sample Count Watermark Setting Bit 4 */
#define FXOS_F_SETUP_F_WMRK5                    (uint8_t)(0x20) /* FIFO Sample Count Watermark Setting Bit 5 */
#define FXOS_F_SETUP_F_MODE0                    (uint8_t)(0x40) /* FIFO Operating Mode Selection Bit 0 */
#define FXOS_F_SETUP_F_MODE1                    (uint8_t)(0x80) /* FIFO Operating Mode Selection Bit 1 */
#define FXOS_F_SETUP_F_MODE_0                   (uint8_t)(0x00) /* 00: FIFO disabled mode */
#define FXOS_F_SETUP_F_MODE_1                   (uint8_t)(0x40) /* 01: Circular buffer mode */
#define FXOS_F_SETUP_F_MODE_2                   (uint8_t)(0x80) /* 10: Stop mode */
#define FXOS_F_SETUP_F_MODE_3                   (uint8_t)(0xC0) /* 11: Trigger mode */

/* FXOS_TRIG_CFG Bits (0x0A) */

#define FXOS_TRIG_CFG_A_VECM        (uint8_t)(0x02) /* Acceleration vector magnitude FIFO trigger enable */
#define FXOS_TRIG_CFG_FFMT          (uint8_t)(0x04) /* Freefall/motion interrupt FIFO trigger enable */
#define FXOS_TRIG_CFG_PULSE         (uint8_t)(0x08) /* Pulse interrupt FIFO trigger enable */
#define FXOS_TRIG_CFG_LNDPRT        (uint8_t)(0x10) /* Landscape/Portrait Orientation interrupt FIFO trigger enable */
#define FXOS_TRIG_CFG_TRANS         (uint8_t)(0x20) /* Transient interrupt FIFO trigger enable */

/* FXOS_SYSMOD Bits (0x0B) */

#define FXOS_SYSMOD0                    (uint8_t)(0x01) /* System Mode Bit 0 */
#define FXOS_SYSMOD1                    (uint8_t)(0x02) /* System Mode Bit 1 */
#define FXOS_SYSMOD_0                    (uint8_t)(0x00) /* System Mode: Standby */
#define FXOS_SYSMOD_1                    (uint8_t)(0x01) /* System Mode: Wake Mode */
#define FXOS_SYSMOD_2                    (uint8_t)(0x02) /* System Mode: Sleep */
#define FXOS_SYSMOD_FGT0                    (uint8_t)(0x04) /* Number of ODR time units since fgerr asserted Bit 0 */
#define FXOS_SYSMOD_FGT1                    (uint8_t)(0x08) /* Number of ODR time units since fgerr asserted Bit 1 */
#define FXOS_SYSMOD_FGT2                    (uint8_t)(0x10) /* Number of ODR time units since fgerr asserted Bit 2 */
#define FXOS_SYSMOD_FGT3                    (uint8_t)(0x20) /* Number of ODR time units since fgerr asserted Bit 3 */
#define FXOS_SYSMOD_FGT4                    (uint8_t)(0x40) /* Number of ODR time units since fgerr asserted Bit 4 */
#define FXOS_SYSMOD_FGERR                    (uint8_t)(0x80) /* FIFO Gate Error Flag */

/* FXOS_INT_SOURCE Bits (0x0C) */

#define FXOS_INT_SRC_DRDY           (uint8_t)(0x01) /* Data Ready interrupt status bit */
#define FXOS_INT_SRC_A_VECM         (uint8_t)(0x02) /* Accelerometer Vector Magnitude interrupt status bit */
#define FXOS_INT_SRC_FFMT         (uint8_t)(0x04) /* Freefall/motion interrupt status bit */
#define FXOS_INT_SRC_PULSE         (uint8_t)(0x08) /* Pulse interrupt status bit */
#define FXOS_INT_SRC_LNDPRT         (uint8_t)(0x10) /* Landscape/Portrait Orientation interrupt status bit*/
#define FXOS_INT_SRC_TRANS         (uint8_t)(0x20) /* Transient interrupt status bit */
#define FXOS_INT_SRC_FIFO         (uint8_t)(0x40) /* FIFO interrupt status bit */
#define FXOS_INT_SRC_ASLP         (uint8_t)(0x80) /* Auto-sleep/wake interrupt status bit */

/* FXOS_XYZ_DATA_CFG Bits (0x0E) */

#define FXOS_XYZ_DATA_CFG_FS0               (uint8_t)(0x01) /* Full Scale Range Selection Bit 0 */
#define FXOS_XYZ_DATA_CFG_FS1               (uint8_t)(0x02) /* Full Scale Range Selection Bit 1 */
#define FXOS_XYZ_DATA_CFG_FS_0               (uint8_t)(0x00) /* 2G Full Scale Range Selection */
#define FXOS_XYZ_DATA_CFG_FS_1               (uint8_t)(0x01) /* 4G Full Scale Range Selection */
#define FXOS_XYZ_DATA_CFG_FS_2               (uint8_t)(0x02) /* 8G Full Scale Range Selection */
#define FXOS_XYZ_DATA_CFG_FS_2G               (uint8_t)(0x00) /* 2G Full Scale Range Selection - Same as above */
#define FXOS_XYZ_DATA_CFG_FS_4G               (uint8_t)(0x01) /* 4G Full Scale Range Selection - Same as above */
#define FXOS_XYZ_DATA_CFG_FS_8G               (uint8_t)(0x02) /* 8G Full Scale Range Selection - Same as above */
#define FXOS_XYZ_DATA_CFG_HPF_OUT               (uint8_t)(0x01) /* High Pass Filter Enable on Accelerometer Data */

/* FXOS_HP_FILTER_CUTOFF Bits (0x0F) */

#define FXOS_HP_FILTER_CUTOFF_SEL0                  (uint8_t)(0x01) /* HPF Cutoff Frequency Selection Bit 0(Table in Datasheet) */
#define FXOS_HP_FILTER_CUTOFF_SEL1                  (uint8_t)(0x02) /* HPF Cutoff Frequency Selection Bit 1(Table in Datasheet) */
#define FXOS_HP_FILTER_CUTOFF_PULSE_LPF_EN          (uint8_t)(0x10) /* LPF Enable Bit for Pulse Processing */
#define FXOS_HP_FILTER_CUTOFF_PULSE_HPF_BYP         (uint8_t)(0x20) /* HPF Bypass Bit for Pulse Processing */

/* FXOS_PL_STATUS Bits (0x10) */

#define FXOS_PL_STATUS_BAFRO                    (uint8_t)(0x01) /* 0: Front facing orientation, 1: Back facing orientation */
#define FXOS_PL_STATUS_LAPO0                    (uint8_t)(0x02) /* Landscape/Portrait Orientation Bit 0 */
#define FXOS_PL_STATUS_LAPO1                    (uint8_t)(0x04) /* Landscape/Portrait Orientation Bit 1 */
#define FXOS_PL_STATUS_LAPO_0                    (uint8_t)(0x00) /* Portrait up Orientation */
#define FXOS_PL_STATUS_LAPO_1                    (uint8_t)(0x02) /* Portrait Down Orientation */
#define FXOS_PL_STATUS_LAPO_2                    (uint8_t)(0x04) /* Landscape Right Orientation */
#define FXOS_PL_STATUS_LAPO_3                    (uint8_t)(0x06) /* Landscape Left Orientation */
#define FXOS_PL_STATUS_LO                    (uint8_t)(0x40) /* Z-tilt angle Lockout */
#define FXOS_PL_STATUS_NEWLP                    (uint8_t)(0x80) /* Landscape/Portrait Status Change Flag */

/* FXOS_PL_CFG Bits (0x11) */

#define FXOS_PL_CFG_EN                  (uint8_t)(0x40) /* Portrait/landscape detection enable */
#define FXOS_PL_CFG_DBCNTM                  (uint8_t)(0x80) /* Debounce counter mode selection */

/* FXOS_PL_BF_ZCOMP Bits (0x13) */

#define FXOS_PL_BF_ZCOMP_ZLOCK0                 (uint8_t)(0x01) /* Z-lock angle threshold Bit 0 - Table in Datasheet */
#define FXOS_PL_BF_ZCOMP_ZLOCK1                 (uint8_t)(0x02) /* Z-lock angle threshold Bit 1 - Table in Datasheet */
#define FXOS_PL_BF_ZCOMP_ZLOCK2                 (uint8_t)(0x04) /* Z-lock angle threshold Bit 2 - Table in Datasheet */
#define FXOS_PL_BF_ZCOMP_BKFR0                 (uint8_t)(0x40) /* Back/front trip angle Threshold Bit 0 - Table in Datasheet */
#define FXOS_PL_BF_ZCOMP_BKFR1                 (uint8_t)(0x80) /* Back/front trip angle Threshold Bit 1 - Table in Datasheet */

/* FXOS_PL_THS_REG Bits (0x14) */

#define FXOS_PL_THS_REG_HYS0                    (uint8_t)(0x01) /* Hysteresis Trip Angle Setting Bit 0 - Table in Datasheet */
#define FXOS_PL_THS_REG_HYS1                    (uint8_t)(0x02) /* Hysteresis Trip Angle Setting Bit 1 - Table in Datasheet */
#define FXOS_PL_THS_REG_HYS2                    (uint8_t)(0x04) /* Hysteresis Trip Angle Setting Bit 2 - Table in Datasheet */
#define FXOS_PL_THS_REG_THS0                    (uint8_t)(0x08) /* Threshold Angle Lookup Setting Bit 0 - Table in Datasheet */
#define FXOS_PL_THS_REG_THS1                    (uint8_t)(0x10) /* Threshold Angle Lookup Setting Bit 1 - Table in Datasheet */
#define FXOS_PL_THS_REG_THS2                    (uint8_t)(0x20) /* Threshold Angle Lookup Setting Bit 2 - Table in Datasheet */
#define FXOS_PL_THS_REG_THS3                    (uint8_t)(0x40) /* Threshold Angle Lookup Setting Bit 3 - Table in Datasheet */
#define FXOS_PL_THS_REG_THS4                    (uint8_t)(0x80) /* Threshold Angle Lookup Setting Bit 4 - Table in Datasheet */

/* FXOS_A_FFMT_CFG Bits (0x15) */



/* FXOS_A_FFMT_SRC Bits (0x16) */



/* FXOS_A_FFMT_THS Bits (0x17) */



/* FXOS_A_FFMT_COUNT Bits (0x18) */



/* FXOS_TRANSIENT_CFG Bits (0x1D) */



/* FXOS_TRANSIENT_SRC (0x1E)*/



/* FXOS_TRANSIENT_THS (0x1F) */



/* FXOS_PULSE_CFG (0x20)*/



/* FXOS_PULSE_SRC (0x22)*/



/* FXOS_PULSE_THSX (0x23)*/



/* FXOS_PULSE_THSY (0x24) */



/* FXOS_PULSE_THSZ (0x25) */



/* FXOS_PULSE_TMLT (0x26) */



/* FXOS_PULSE_LTCY (0x27)*/



/* FXOS_PULSE_WIND (0x28) */



/* FXOS_CTRL_REG1 (0x2A) */

#define FXOS_CTRL_REG1_ACTIVE                   (uint8_t)(0x01) /* Standby/Active Mode Control Bit */
#define FXOS_CTRL_REG1_F_READ                   (uint8_t)(0x02) /* 1: Fast-read Mode (8-bit output) */
#define FXOS_CTRL_REG1_LNOISE                   (uint8_t)(0x04) /* 0: Normal, 1: Reduce noise mode */
#define FXOS_CTRL_REG1_DR0                      (uint8_t)(0x08) /* Output Data Rate Selection Bit 0 - Table in Datasheet */
#define FXOS_CTRL_REG1_DR1                      (uint8_t)(0x10) /* Output Data Rate Selection Bit 1 - Table in Datasheet */
#define FXOS_CTRL_REG1_DR2                      (uint8_t)(0x20) /* Output Data Rate Selection Bit 2 - Table in Datasheet */
#define FXOS_CTRL_REG1_ASLP_RATE0               (uint8_t)(0x40) /* Auto-wake Sample Frequency Selection Bit 0 - Table in Datasheet */
#define FXOS_CTRL_REG1_ASLP_RATE1               (uint8_t)(0x80) /* Auto-wake Sample Frequency Selection Bit 1 - Table in Datasheet */

/* FXOS_CTRL_REG2 (0x2B) */

#define FXOS_CTRL_REG2_MODS0                    (uint8_t)(0x01) /* Accelerometer Wake Mode OSR Selection Bit 0 */
#define FXOS_CTRL_REG2_MODS1                    (uint8_t)(0x02) /* Accelerometer Wake Mode OSR Selection Bit 1 */
#define FXOS_CTRL_REG2_SLPE                    (uint8_t)(0x04) /* Auto-sleep Mode Enable Bit */
#define FXOS_CTRL_REG2_SMODS0                    (uint8_t)(0x08) /* Accelerometer sleep Mode OSR Selection Bit 0 */
#define FXOS_CTRL_REG2_SMODS1                    (uint8_t)(0x10) /* Accelerometer sleep Mode OSR Selection Bit 1 */
#define FXOS_CTRL_REG2_RST                    (uint8_t)(0x40) /* Software Reset Enable Bit */
#define FXOS_CTRL_REG2_ST                    (uint8_t)(0x80) /* Self-test enable */
/* FXOS_CTRL_REG3 (0x2C) */

#define FXOS_CTRL_REG3_PP_OD                     (uint8_t)(0x01) /* INT1/INT2 Push-Pull or Open Drain Output Mode Selection */
#define FXOS_CTRL_REG3_IPOL                      (uint8_t)(0x02) /* INT1/INT2 Interrupt logic polarity */
#define FXOS_CTRL_REG3_WAKE_A_VECM               (uint8_t)(0x04) /* Acceleration vector-magnitude function enabled in sleep mode */
#define FXOS_CTRL_REG3_WAKE_FFMT                 (uint8_t)(0x08) /* Freefall/motion function enabled in sleep mode */
#define FXOS_CTRL_REG3_WAKE_PULSE                (uint8_t)(0x10) /* Pulse function enabled in sleep mode */
#define FXOS_CTRL_REG3_WAKE_LANDPRT              (uint8_t)(0x20) /* Orientation function enabled in sleep mode */
#define FXOS_CTRL_REG3_WAKE_TRAN                 (uint8_t)(0x40) /* Transient Function enabled in sleep Mode */
#define FXOS_CTRL_REG3_FIFO_GATE                 (uint8_t)(0x80) /* FIFO gate bypass Enable Bit */

/* FXOS_CTRL_REG4 (0x2D) */

#define FXOS_CTRL_REG4_INT_DRDY                 (uint8_t)(0x01) /* Data Ready Interrupt Enable */
#define FXOS_CTRL_REG4_INT_A_VECM                 (uint8_t)(0x02) /* Acceleration Vector-Magnitude Interrupt Enable */
#define FXOS_CTRL_REG4_INT_FFMT                 (uint8_t)(0x04) /* Freefall/Motion Interrupt Enable */
#define FXOS_CTRL_REG4_INT_PULSE                 (uint8_t)(0x08) /* Pulse Interrupt Enable */
#define FXOS_CTRL_REG4_INT_LNDPRT                 (uint8_t)(0x10) /* Orientation interrupt Enable */
#define FXOS_CTRL_REG4_INT_TRANS                 (uint8_t)(0x20) /* Transient Interrupt Enable */
#define FXOS_CTRL_REG4_INT_FIFO                 (uint8_t)(0x40) /* FIFO interrupt enable */
#define FXOS_CTRL_REG4_INT_ASLP                 (uint8_t)(0x80) /* Sleep interrupt Enable */

/* FXOS_CTRL_REG5 (0x2E) */

#define FXOS_CTRL_REG5_INTCFG_DRDY               (uint8_t)(0x01) /* 0: DRDY Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_A_VECM               (uint8_t)(0x02) /* 0: A_VECM Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_FFMT               (uint8_t)(0x04) /* 0: FFMT Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_PULSE               (uint8_t)(0x08) /* 0: PULSE Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_LNDPRT               (uint8_t)(0x10) /* 0: LNDPRT Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_TRANS               (uint8_t)(0x20) /* 0: TRANS Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_FIFO               (uint8_t)(0x40) /* 0: FIFO Interrupt routed to INT2 1: Interrupt to INT 1 */
#define FXOS_CTRL_REG5_INTCFG_ASLP               (uint8_t)(0x80) /* 0: ASLP Interrupt routed to INT2 1: Interrupt to INT 1 */

/* FXOS_M_THS_CFG (0X52) */



/* FXOS_M_THS_SRC (0X53) */



/* FXOS_M_CTRL_REG1 (0x5B)*/

#define FXOS_M_CTRL_REG1_HMS0                   (uint8_t)(0x01) /* Hybrid Mode Selection Bit 0 */
#define FXOS_M_CTRL_REG1_HMS1                   (uint8_t)(0x02) /* Hybrid Mode Selection Bit 0 */
#define FXOS_M_CTRL_REG1_HMS_0                   (uint8_t)(0x00) /* Hybrid Mode Selection: Only Accelerometer Enabled */
#define FXOS_M_CTRL_REG1_HMS_1                   (uint8_t)(0x01) /* Hybrid Mode Selection: Only Magnetometer Enabled */
#define FXOS_M_CTRL_REG1_HMS_2                   (uint8_t)(0x03) /* Hybrid Mode Selection: Hybrid Mode: Accel/Mag Both Enabled */
#define FXOS_M_CTRL_REG1_OS0                   (uint8_t)(0x04) /* Oversample Ratio for Magnetometer Bit 0 - Table in Datasheet */
#define FXOS_M_CTRL_REG1_OS1                   (uint8_t)(0x08) /* Oversample Ratio for Magnetometer Bit 1 - Table in Datasheet */
#define FXOS_M_CTRL_REG1_OS2                   (uint8_t)(0x10) /* Oversample Ratio for Magnetometer Bit 2 - Table in Datasheet */
#define FXOS_M_CTRL_REG1_OST                   (uint8_t)(0x20) /* One-shot triggered magnetic measurement mode */
#define FXOS_M_CTRL_REG1_RST                   (uint8_t)(0x40) /* One-shot magnetic reset degauss control bit */
#define FXOS_M_CTRL_REG1_ACAL                   (uint8_t)(0x80) /* Magnetic hard-iron offset auto-calibration enable bit */

/* FXOS_M_CTRL_REG2 (0x5C)*/

#define FXOS_M_CTRL_REG2_RST_CNT0                        (uint8_t)(0x01) /* Magnetic sensor reset frequency Bit 0 - Table in Datasheet */
#define FXOS_M_CTRL_REG2_RST_CNT1                        (uint8_t)(0x02) /* Magnetic sensor reset frequency Bit 1 - Table in Datasheet */
#define FXOS_M_CTRL_REG2_RST_MAXMINRST                   (uint8_t)(0x04) /* Magnetic measurement min/max function reset */
#define FXOS_M_CTRL_REG2_RST_MAXMINDISABLETHS            (uint8_t)(0x08) /* Magnetic measurement min/max function disable during THS event*/
#define FXOS_M_CTRL_REG2_RST_MAXMINDISABLE               (uint8_t)(0x10) /* Magnetic Measurement min/max detection function disable */
#define FXOS_M_CTRL_REG2_HYBAUTOINC                  (uint8_t)(0x20) /* AUTOINC to Magnetometer Data in hybrid mode */

/* FXOS_M_CTRL_REG3 (0x5D)*/



/* FXOS_M_INT_SRC (0x5E)*/



/* FXOS_A_VECM_CFG (0X5F) */



/* FXOS_M_VECM_CFG (0X69)*/



#endif /* FXOS8700_H_ */
