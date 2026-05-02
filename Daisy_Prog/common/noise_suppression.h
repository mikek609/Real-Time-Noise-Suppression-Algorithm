#include <cstddef>
#include <cstdint>
#include <limits>
#include <cmath>
#include <algorithm>

#define BIN_FRAMES      312
#define LAMBDA          0.05
#define ALPHA           20
#define N               256 //FFT SIZE
#define OVERSAMP        4   //oversampling factor
#define NUM_FREQ_BINS   128
#define FRAME_INC       64  //size of frames
#define PI              3.14159 // added

typedef struct{
    float M1[NUM_FREQ_BINS]; //these four track the noise floor per bin
    float M2[NUM_FREQ_BINS];
    float M3[NUM_FREQ_BINS];
    float M4[NUM_FREQ_BINS];
    float mmse[NUM_FREQ_BINS]; //minimum across m1-m4
    float overlap_buf[N]; //tail of previous frame for overlap-add
    float ola_buf[N]; //tail of previous frame for output overlap
    float window[N]; //coefficiant for frame shape
    int count_min;
}NS_State;

void ns_init(NS_State& state);

void ns_process_block(NS_State& state, const float* input, float* output);
