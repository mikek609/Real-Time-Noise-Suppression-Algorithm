#include "fft_wrapper.h"
#include <cmath>

#define PI              3.14159

//Populates a complex array using Eulers formula based off of the frames we give it
void fft_forward(const float* real_in, NS_Complex* complex_out, int n){
    for(int k = 0; k < n; k++){
        complex_out[k] = 0;
        for(int j = 0; j < n; j++){
            complex_out[k] += real_in[j] * NS_Complex(cos(2*PI*j*k/n), -sin(2*PI*j*k/n)); 
        }
    }
}

//Takes a complex array and turns it into th real values
void fft_inverse(NS_Complex* complex_in, float* real_out, int n){
    for(int k = 0; k < n; k++){
        NS_Complex sum = 0;
        for(int j=0; j< n; j++){
            sum += complex_in[j] * NS_Complex(cos(2*PI*j*k/n), sin(2*PI*j*k/n));
        }
        real_out[k] = sum.real() / n;
    }
}