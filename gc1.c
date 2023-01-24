#include <math.h>

void goertzel(float* samples, int num_samples, float target_freq, float* real, float* imag)
{
    float omega, sine, cosine, coeff, q0, q1, q2;
    int i;

    omega = 2.0 * M_PI * target_freq / (float) SAMPLING_RATE;
    sine = sin(omega);
    cosine = cos(omega);
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


\\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>
#include <math.h>

int main()
{
    int N = 100; // Number of samples
    int k = 10; // Frequency component of interest

    double x[N]; // Input signal
    double X_k = 0.0; // Goertzel output
    double w = 2.0 * M_PI * k / N; // Frequency component
    double cos_w = cos(w);
    double sin_w = sin(w);
    double coeff = 2.0 * cos_w;
    
    double q0 = 0.0;
    double q1 = 0.0;
    double q2 = 0.0;
    int i;

    // Read in sample data
    for(i = 0; i < N; i++) {
        scanf("%lf", &x[i]);
    }

    // Run the Goertzel algorithm
    for(i = 0; i < N; i++) {
        q0 = coeff * q1 - q2 + x[i];
        q2 = q1;
        q1 = q0;
    }

    // Calculate the output
    X_k = q1 - q2 * cos_w;

    // Print the output
    printf("X[%d] = %f\n", k, X_k);

    return 0;
}
\\\\\\\\\\\\\\\\\\\\\\
