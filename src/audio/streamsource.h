#pragma once

#include <stdbool.h>
#include <AL/al.h>

#include "source.h"
#include "decoder.h"

typedef struct {
  audio_SourceCommon common;
  audio_StreamSourceDecoder const* decoder;
  void*  decoderData;
  ALuint buffers[2];
  bool   looping;
} audio_StreamSource;

bool audio_loadStream(audio_StreamSource *source, char const * filename);
void audio_StreamSource_play(audio_StreamSource *source);
void audio_StreamSource_setLooping(audio_StreamSource *source, bool loop);
void audio_updateStreams(void);
void audio_streamsource_init(void);
void audio_StreamSource_stop(audio_StreamSource *source);
void audio_StreamSource_rewind(audio_StreamSource *source);
void audio_StreamSource_pause(audio_StreamSource *source);
void audio_StreamSource_resume(audio_StreamSource *source);
