# Common

This folder contains hardware-independent source files shared between the PC 
validation harness and the Daisy Seed embedded firmware. Any file here should 
compile cleanly for both targets with no modification.

## Contents

- noise_suppression.h / noise_suppression.cpp — core spectral subtraction noise
  suppression algorithm, ported from the MATLAB prototype
- fft_wrapper.h — thin FFT interface used by the algorithm. Implemented by either
  fft_wrapper_pc.cpp (PC validation) or fft_wrapper_cmsis.cpp (Daisy embedded)
- dr_wav.h — wav proccessing header for pc side validation

## Validation Strategy

The algorithm is being validated in two phases:

  Phase 1 — Offline PC: a standalone harness reads a noisy WAV file, runs it 
  through the algorithm, and writes the output. SNR is compared against the 
  MATLAB prototype to verify correctness before touching hardware.

  Phase 2 — Embedded: once Phase 1 passes, the same source files are compiled
  into the Daisy firmware and validated via listening tests and SNR benchmarking
  on hardware.

## Algorithm Overview

Hamming-windowed overlap-add STFT framework with an MMSE-based noise estimator.
Key parameters: FFT size N=256, oversampling factor 4, frame increment 64,
BIN_FRAMES=312, lambda=0.05, alpha=20.

— Daniel