#include "staticsource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav_decoder.h"
#include "vorbis_decoder.h"

static audio_wav_DecoderData* wav;
//static audio_vorbis_DecoderData* vorbis;

static const char* get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot+1;
}

void audio_loadStatic(audio_StaticSource *source, char const * filename) {
  audio_SourceCommon_init(&source->common);

  alGenBuffers(1, &source->buffer);
  //audio_vorbis_load(source->buffer, filename);
  audio_wav_load(source->buffer, filename);
  alSourcei(source->common.source, AL_BUFFER, source->buffer);
}

void audio_StaticSource_play(audio_StaticSource *source) {
  if(source->common.state != audio_SourceState_playing) {
    audio_SourceCommon_play(&source->common);
    printf("%d /n",source->buffer);
  }
}

void audio_StaticSource_setLooping(audio_StaticSource *source, bool loop) {
  alSourcei(source->common.source, AL_LOOPING, loop);
}


void audio_StaticSource_stop(audio_StaticSource *source) {
  audio_SourceCommon_stop(&source->common);
  audio_StaticSource_rewind(source);
}


void audio_StaticSource_rewind(audio_StaticSource *source) {
  alSourceRewind(source->common.source);

  if(source->common.state == audio_SourceState_playing) {
    audio_SourceCommon_play(&source->common);
  }
}


void audio_StaticSource_pause(audio_StaticSource *source) {
  audio_SourceCommon_pause(&source->common);
}


void audio_StaticSource_resume(audio_StaticSource *source) {
  audio_SourceCommon_resume(&source->common);
}
