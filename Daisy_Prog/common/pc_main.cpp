#include "dr_wav.h"
#include "noise_suppression.h"
#include <vector>
#include <cstdio>

int main() {
    //reading wav section
    drwav wav;
    if(!drwav_init_file(&wav, "input.wav", nullptr)){
        //input wav needs to be changed to our noisy audio
        fprintf(stderr, "Error in opening our wav file");
    }

    drwav_uint64 totalFrames = wav.totalPCMFrameCount;
    drwav_uint32 channels = wav.channels;
    drwav_uint32 samplerate = wav.sampleRate;

    if(channels != 1){
        fprintf(stderr, "Warning: only works with mono chanels, got %u channels\n", channels);
        drwav_uninit(&wav);
        return 1;
    }

    std::vector<float> raw_buffer(totalFrames*channels);

    drwav_uint64 FramesRead = drwav_read_pcm_frames_f32(&wav, totalFrames, raw_buffer.data());

    if(FramesRead != totalFrames){
        fprintf(stderr, "Warning: expected %llu frames, got %llu \n", totalFrames, FramesRead);
    }

    drwav_uninit(&wav);
    
    //processing section
    NS_State noise_state;
    ns_init(noise_state);

    std::vector<float> clean_buf(totalFrames);

    for(drwav_uint64 i=0; i + FRAME_INC <= totalFrames; i+= FRAME_INC){
        ns_process_block(noise_state, &raw_buffer[i], &clean_buf[i]);
    }

    //building the output
    drwav_data_format format;
    format.container     = drwav_container_riff; //standard .wav file
    format.format        = DR_WAVE_FORMAT_IEEE_FLOAT; //store as a 32 bit float
    format.channels      = channels;
    format.sampleRate    = samplerate;
    format.bitsPerSample = 32;

    drwav wavOut;
    if(!drwav_init_file_write(&wavOut, "clean.wav", &format, nullptr)){
        fprintf(stderr, "Error in writing clean wav file");
    }

    drwav_uint64 FramesWritten = drwav_write_pcm_frames(&wavOut, totalFrames, clean_buf.data());

    drwav_uninit(&wavOut);
    return 0;
}