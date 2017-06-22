/*
 * servo.h
 *
 *  Created on: May 12, 2017
 *      Author: Eric
 */

#ifndef SERVO_H_
#define SERVO_H_

void setPWMFreq(uint8_t freq);
void setPWMDC(uint8_t servo, float dc);
void setServoPosition(uint8_t servo, uint8_t degrees);



#endif /* SERVO_H_ */
