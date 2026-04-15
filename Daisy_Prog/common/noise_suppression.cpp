#include "noise_suppression.h"
#include "fft_wrapper.h"

NS_State state;

static constexpr float EPS = 1e-10f;

//Noise state init 
void ns_init(NS_State& state){
    state.count_min = 0;
//populating overlap buf with zeros and window shape (hamming coefficients)
    for(int i=0; i< N; i++)
    {
        state.window[i] = sqrt((1-0.85185*cos((2*i+1)* M_PI/N))/OVERSAMP);
        state.overlap_buf[i] = 0;
        state.ola_buf[i] = 0;
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


//This function processes one frame at a time
void ns_process_block(NS_State& state, const float* input, float* output){
    //first we build our frames
    float frame[N];
    NS_Complex fft_buf[N];

    //First part: tail of overlap buffer (samples FRAME_INC to N-1)
    for(int i=0; i<N-FRAME_INC; i++){
        frame[i] = state.overlap_buf[i + FRAME_INC];
    }
    //Second part: new incoming samples
    for(int i = 0; i < FRAME_INC; i++){
        frame[N-FRAME_INC + i] = input[i];
    }

    //applying the frame coefficients 
    for(int i = 0; i<N; i++){
        state.overlap_buf[i] = frame[i];
        frame[i] *= state.window[i];
    }
    
    //transforming our real frames into a complex array 
    fft_forward(frame, fft_buf, N);

    //Now we want to compute the magnitude min 
    float mag[NUM_FREQ_BINS];
    for(int k = 0; k<NUM_FREQ_BINS; k++){
        mag[k] = std::abs(fft_buf[k]);
    }

    for(int k = 0; k < NUM_FREQ_BINS; k++){
        state.M1[k] = std::min(state.M1[k], mag[k]);
    }
    state.count_min++;

    if(state.count_min >= BIN_FRAMES){
        state.count_min = 0;
        for(int k =0; k< NUM_FREQ_BINS; k++){
            state.M4[k] = state.M3[k];
            state.M3[k] = state.M2[k];
            state.M2[k] = state.M1[k];
            state.M1[k] = mag[k]; //resets M1 to our current frame
        }
    }


    float g[NUM_FREQ_BINS];
    //computing the running min across all four buffers
    for(int k = 0; k< NUM_FREQ_BINS; k++){
        state.mmse[k] = std::min({state.M1[k], state.M2[k], state.M3[k], state.M4[k]});

        //calculating the gain
        g[k] = std::max((float)LAMBDA, 1.0f - ALPHA* state.mmse[k] / (mag[k]+ EPS));

        fft_buf[k]  *= g[k]; //apply gain
    }

    //building upper half of spectrum as mirror image
    for(int k = 1; k < NUM_FREQ_BINS; k++){    
        fft_buf[N-k] = std::conj(fft_buf[k]);
    }

    float time_output[N];

    fft_inverse(fft_buf, time_output, N);

    //windowing our output
    for(int i = 0; i < N; i++){
        time_output[i] *= state.window[i];
    }

    //adding the saved tail
    for(int i = 0; i < N - FRAME_INC; i++){
        time_output[i] += state.ola_buf[i];
    }

    for(int i=0; i < FRAME_INC; i++){
        output[i] = time_output[i];
    }

    for(int i=0 ; i < N - FRAME_INC; i++){
        state.ola_buf[i] = time_output[i + FRAME_INC];
    }
}