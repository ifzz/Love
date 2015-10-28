#pragma once

#include <AL/al.h>
#include <alloca.h>

typedef struct {
  ALshort    *readBuffer;
  int         readBufferSize;
  int         preloadedSamples;
} audio_vorbis_DecoderData;

int audio_vorbis_load(ALuint buffer, char const *filename);
void audio_vorbis_rewindStream(void *decoderData);
int audio_vorbis_getChannelCount(void *decoderData);
int audio_vorbis_getSampleRate(void *decoderData);
void audio_vorbis_flushBuffer(void *decoderData);
