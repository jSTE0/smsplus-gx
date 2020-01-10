#include <stdio.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include "smsplus.h"
#include "sound_output.h"
#include "shared.h"
#include "libretro.h"

extern retro_audio_sample_batch_t audio_batch_cb;

static int16_t buffer_snd[SOUND_FREQUENCY * 2];

void Sound_Init()
{
	option.sndrate = SOUND_FREQUENCY;

	return;
}

void Sound_Update()
{
	int32_t i;
	for (i = 0; i < (4 * (SOUND_FREQUENCY / snd.fps)); i++) 
	{
		buffer_snd[i * 2] = snd.output[1][i] * option.soundlevel;
		buffer_snd[i * 2 + 1] = snd.output[0][i] * option.soundlevel;
	}

	audio_batch_cb((const int16_t*)buffer_snd, (size_t) (SOUND_FREQUENCY / snd.fps));
}

void Sound_Close()
{
}
