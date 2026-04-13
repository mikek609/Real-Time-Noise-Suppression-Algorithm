// Rough porting order

// 1. Get a basic audio passthrough working first (in → out with no processing)
// 2. Add framing and windowing
// 3. Add FFT/IFFT round-trip (input should come back out unchanged)
// 4. Add noise estimation (start with a fixed noise floor captured at startup)
// 5. Add the subtraction step
// 6. Validate against your MATLAB output using the SNR benchmarking scripts you have planned
// This incremental approach will make our life easier when debugging 

#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

//global hardware handler
DaisySeed hardware;

//Our Audio callback - called automatically in libDaisy every block
void AudioCallback(AudioHandle::InputBuffer   in,
                   AudioHandle::OutputBuffer  out,
                   size_t                     size)
{
    for (size_t i = 0; i < size; i++)
    {   
        //pass left and right channels straight through
        out[0][i] = in[0][i];
        out[1][i] = in[1][i];
    }
}

int main(void)
{
    //initializing the daisy seed
    hardware.Init();

    //Setting the audio sample rate (apparently 48kHz is standard)
    hardware.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

    //Start Audio, passing in our callback
    hardware.StartAudio(AudioCallback);

    //loop forever - all work will happen in the callback
    while(true) {}
}