#include <stdlib.h>
#include <math.h>
#include "daisy_seed.h"
#include "arm_math.h"

using namespace daisy;

const int FSAMP = 8000;
const int FFTLEN = 256;
const int OVERSAMP = 4;
// const float PI = 3.14159263589793;

DaisySeed hw;



int main(){
    hw.Configure();
    hw.Init();
}