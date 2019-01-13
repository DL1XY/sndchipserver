/*
 * atari_tia_controller.c
 *
 *  Created on: 09.01.2019
 *      Author: enradion
 */
#include "atari_tia_controller.h"
#include "atari_tia/atari_tia.h"

void InitAtariTIA()
{
	// setup ESP
	// setup Pins
}

void SendConfig(const atari_tia_cfg cfg)
{
	struct atari_tia_audio_registers;

	if (cfg.aud == 0)
	{
		if (cfg.reg == 0)
		{
			atari_tia_audio_registers.aud0_volume = cfg.val;
		} else if (cfg.reg == 1)
		{
			atari_tia_audio_registers.aud0_freq_div = cfg.val;
		} else if (cfg.reg == 2)
		{
			atari_tia_audio_registers.aud0_control = cfg.val;
		}
	}
	else
	{
		if (cfg.reg == 0)
		{
			atari_tia_audio_registers.aud1_volume = cfg.val;
		} else if (cfg.reg == 1)
		{
			atari_tia_audio_registers.aud1_freq_div = cfg.val;
		} else if (cfg.reg == 2)
		{
			atari_tia_audio_registers.aud1_control = cfg.val;
		}
	}

	// send to chip
}

