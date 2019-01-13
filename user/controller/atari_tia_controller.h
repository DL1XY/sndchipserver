/*
 * atari_tia_controller.h
 *
 *  Created on: 09.01.2019
 *      Author: enradion
 */

#ifndef USER_RESOURCES_ATARI_TIA_CONTROLLER_H_
#define USER_RESOURCES_ATARI_TIA_CONTROLLER_H_

#define ESP01_PIN_74HC595_0_SER		2;
#define ESP01_PIN_74HC595_RCLK		4;
#define ESP01_PIN_74HC595_SCLK		4;
#define ESP01_PIN_TIA_RW			4;

#define HIGH						1;
#define LOW							0;

struct atari_tia_cfg_t;

typedef struct atari_tia_cfg_t
{
	uint8 aud;
	uint8 reg;
	uint8 val;
} atari_tia_cfg ;


void InitAtariTIA();
void SendConfig(const atari_tia_cfg cfg);


#endif /* USER_RESOURCES_ATARI_TIA_CONTROLLER_H_ */
