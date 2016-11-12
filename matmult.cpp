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
#include <fstream>

int main(int argc, char *argv[])
{
	std::cout << argc << std::endl;    
//Time file
   
    matrix A, B;
    read(argv[1],A);
    read(argv[2],B);
    double time_n=100, time_o=100, time_blas=100;

    matrix C(A.get_rows(), B.get_cols());
#endif
        siwir::Timer timer;
        timer.reset();
        naivemult(A, B, C);  //blocking removed and multiply
        time_n = std::min(time_n, timer.elapsed());
#ifdef USE_LIKWID
   likwid_markerStopRegion( "Naive" );
#endif
   std::cout << "size "<<A.get_cols() << " time-naive" << time_n << "\t";
   //write(argv[3],C);
    
//Optimized 
#ifdef USE_LIKWID
   likwid_markerStartRegion( "Optimized" );
#endif
	timer.reset();
        multiply(A, B, C); //code with blocking
        time_o = std::min(time_o, timer.elapsed());
#ifdef USE_LIKWID
   likwid_markerStopRegion( "Optimized" );
#endif 
   std::cout << "size " << A.get_cols()<< " time-blocking "<<time_o << std::endl;
   //write(argv[3],C);



//Blas
#ifdef USE_LIKWID
   likwid_markerStartRegion( "BLAS" );
#endif
   int M = A.get_rows(); int N = A.get_cols(); int K = B.get_cols(); 
   int lda = N; int ldb = K; int ldc =K;
      timer.reset();
      cblas_dgemm( CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 1.0, A.data.data(), lda, B.data.data(), ldb, 0.0, C.data.data(), ldc );
      time_blas = std::min(time_blas, timer.elapsed());

#ifdef USE_LIKWID
   likwid_markerStopRegion( "BLAS" );
   likwid_markerClose();
#endif   
   std::cout <<"size "<< A.get_cols() << " time-blas "<< time_blas << std::endl;



return 0;

}
