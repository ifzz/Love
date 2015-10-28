#include "wav_decoder.h"

int audio_wav_load(unsigned int buffer, char const * filename) {
        audio_wav_DecoderData* data = malloc(sizeof(audio_wav_DecoderData));
        FILE* file = fopen(filename, "rb");

        if(file){
                fseek(file,0,SEEK_END);
                data->size = ftell(file);
                fseek(file,0,SEEK_SET);

                data->readBuffer = malloc(data->size - 44);

                fseek(file, 44, SEEK_SET);
                fread(data->readBuffer,1,data->size - 44, file);
                fseek(file,0,SEEK_SET);

                fseek(file, 24, SEEK_SET);
                fread(&data->samplerate, 1, 4, file);
                fseek(file, 0, SEEK_SET);
        }

        data->samplerate *= 1;
        alBufferData(buffer, AL_FORMAT_MONO8, data->readBuffer, data->size, data->samplerate);

        return 1;
}
