#include "audio.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>

static struct {
  ALCdevice  *device;
  ALCcontext *context;
} moduleData;


void audio_init(void) {
  moduleData.device = alcOpenDevice(0);
  moduleData.context = alcCreateContext(moduleData.device, 0);
  if(!alcMakeContextCurrent(moduleData.context)) {
    printf("Failed to initialite audio context\n");
  }
}
