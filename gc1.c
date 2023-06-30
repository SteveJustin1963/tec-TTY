#include <math.h>

#define SAMPLING_RATE 44100

void goertzel(float* samples, int num_samples, float target_freq, float* real, float* imag)
{
    float omega, sine, cosine, coeff, q0, q1, q2;
    int i;

    omega = 2.0 * M_PI * target_freq / (float) SAMPLING_RATE;
    sine = sinf(omega);
    cosine = cosf(omega);
    coeff = 2.0 * cosine;
    q0 = 0;
    q1 = 0;
    q2 = 0;

    for(i = 0; i < num_samples; i++)
    {
        q0 = coeff * q1 - q2 + samples[i];
        q2 = q1;
        q1 = q0;
    }

    *real = (q1 - q2 * cosine) / (float) num_samples;
    *imag = (q2 * sine) / (float) num_samples;
}
