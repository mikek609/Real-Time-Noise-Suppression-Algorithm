#pragma once
#include <complex>

using NS_Complex = std::complex<float>;

void fft_forward(const float* real_in, NS_Complex* complex_out, int n);
void fft_inverse(NS_Complex* complex_in, float* real_out, int n);