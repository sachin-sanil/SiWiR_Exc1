//// this is main /////
#include "Timer.h"
#include <iostream>
#include <vector>

extern "C" {
#include <cblas.h>
}

#ifdef USE_LIKWID
extern "C" {
#include <likwid.h>
}
#endif

#include "matrix.h"
#include "multiply.cpp"
int main()
{

    matrix A, B;
    read("A.in",A);
    read("B.in",B);
    double time = 100.0;

    matrix C(A.get_rows(), B.get_cols());
    
#ifdef USE_LIKWID
   likwid_markerInit();
   likwid_markerStartRegion( "MATRIX" );
#endif
   
        siwir::Timer timer;
        timer.reset();
        multiply(A, B, C);
        time = std::min(time, timer.elapsed());
        
#ifdef USE_LIKWID
   likwid_markerStopRegion( "MATRIX" );
#endif 
   std::cout << "Time_Faducode " << time << std::endl;
    write("C.out",C);





#ifdef USE_LIKWID
   likwid_markerStartRegion( "BLAS" );
#endif
   
   int M = A.get_rows(); int N = A.get_cols(); int K = B.get_cols(); 
   int lda = N; int ldb = K; int ldc =K;
      timer.reset();
      cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 1.0, A.data.data(), lda, B.data.data(), ldb, 0.0, C.data.data(), ldc );
      time = std::min(time, timer.elapsed());

#ifdef USE_LIKWID
   likwid_markerStopRegion( "BLAS" );
   likwid_markerClose();
#endif   

std::cout << "Time_BLAS " << time << std::endl;

return 0;

}
