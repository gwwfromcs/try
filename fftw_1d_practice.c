// Compile: 
// On ICES machine, 
// 1. module load fftw3/3.3.4 intel/17.0; 
// 2. icc -I$FFTW_INC -L$FFTW_LIB -lfftw3 fftw_1d_practice.c -o fftw_1d_practice.exe
// 3. ./fftw_1d_practice.exe > data.txt
#include <complex.h>
#include <fftw3.h>
#include <math.h>

int main()
{
    fftw_plan p;
    int i, N = 500, nsquare = 10, offset=1;
    double sigma = 0.001, or, oi;
    fftw_complex in[N];
    fftw_complex out[N];

    for(i = 0; i<N; i++) {
        // in[i] = cos( 3.1415926 * 8.0 * (float)i/N ) + I * sin( 3.1415926 * 8.0 * (float)i/N ) ;
        
        // Square wave 1
        if(i < nsquare+offset || i > N-nsquare+offset) {
            in[i] = 1.0;
        }
        else { in[i] = 0.0;}

        // Square wave 2
        /*
        if(i < nsquare*2-1 ) {
            in[i] = 1.0;
        }
        else { in[i] = 0.0;}
        */

        // Gaussian function
        /*
        in[i] = sqrt(1./(2.*3.1415926*sigma)) * exp(-((float)i/N-0.0)*((float)i/N-0.0)/(2.0*sigma*sigma)) +  \
          sqrt(1./(2.*3.1415926*sigma)) * exp(-((float)i/N-1.0)*((float)i/N-1.0)/(2.0*sigma*sigma));
        */

        // Delta function
        /*
        if(i==0) {
            in[i] = 2.0;
        }
        else {
            in[i] = 0.0;
        }
        */
    };
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);
    
    printf("#  out = fft(in) \n");
    printf("#    x   real(in(x))   imag(in(x))   real(out)   imag(out)   mod(out) \n");
    for(i = 0; i<N; i++) {
        or=creal(out[i]);
        oi=cimag(out[i]);
        printf("  %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n", (float)i/N,creal(in[i]),cimag(in[i]),or,oi,sqrt( or*or + oi*oi ));
    }

    fftw_destroy_plan(p);
    return 0;
}
