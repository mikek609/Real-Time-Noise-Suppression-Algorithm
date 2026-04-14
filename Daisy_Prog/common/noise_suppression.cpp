#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include "noise_suppression.h"

NS_State state;

void fft_forward(float* windowed_buf){
    //stub for the sake of getting noise_process logic down first
}


//Noise state init 
void ns_init(NS_State& state){
    state.count_min = 0;
//populating overlap buf with zeros and window shape (coefficients)
    for(int i=0; i< N; i++)
    {
        state.window[i] = sqrt((1-0.85185*cos((2*i+1)* M_PI/N))/OVERSAMP);
        state.overlap_buf[i]=0;
    }

//Setting the Ms to infinity so that the first real value is immediately the min        
    for(int i=0; i< NUM_FREQ_BINS; i++)
    {
        state.M1[i] = std::numeric_limits<float>::infinity();
        state.M2[i] = std::numeric_limits<float>::infinity();
        state.M3[i] = std::numeric_limits<float>::infinity();
        state.M4[i] = std::numeric_limits<float>::infinity();
    }
}



void ns_process_block(NS_State& state, const float* input, float* output){
    //first we build our frames
    float frame[N];
    //First part: tail of overlap buffer (samples FRAME_INC to N-1)
    for(int i=0; i<N-FRAME_INC; i++){
        frame[i] = state.overlap_buf[i + FRAME_INC];
    }
    //Second part: new incoming samples
    for(int i = 0; i < FRAME_INC; i++){
        frame[N-FRAME_INC + i] = input[i];
    }

    for(int i = 0; i<N; i++){
        state.overlap_buf[i] = frame[i];
        frame[i] *= state.window[i];
    }
    
    fft_forward(frame);

}

