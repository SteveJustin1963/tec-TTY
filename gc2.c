#include <stdio.h>
#include <math.h>

int main()
{
    int N = 100; // Number of samples
    int k = 10; // Frequency component of interest

    double x[N]; // Input signal
    double X_real, X_imag; // Goertzel output
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
    X_real = (q1 - q2 * cos_w) / (double) N;
    X_imag = (q2 * sin_w) / (double) N;

    // Print the output
    printf("X[%d] = %f + j%f\n", k, X_real, X_imag);

    return 0;
}
