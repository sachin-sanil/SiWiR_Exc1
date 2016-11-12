#include <iostream>
#include <vector>

void naivemult(matrix& A, matrix& B, matrix& C)
{

    
    assert((A.cols == B.rows) && (A.rows == C.rows) && (B.cols == C.cols));
    int p = A.rows;
    int q = A.cols;
    int r = C.cols;
    for (auto i = 1; i <= p; ++i  ){
    for (auto k = 1; k<= r; ++k) {
    for (auto j = 1; j<= q; ++j){

            C(i,k) += A(i,j) * B(j,k);

    }
    }
    }
    
}


void multiply(matrix& A, matrix& B, matrix& C)
{
  
    
    
    assert((A.cols == B.rows) && (A.rows == C.rows) && (B.cols == C.cols));
    int b = 32;
    if (!(A.cols == A.rows && B.rows == B.cols && A.cols%b==0))
        b = 1;
    
    int n = A.cols/b;
        
    for(auto ii=1;  ii<=n;   ++ii)
    for(auto kk=1;  kk<=n;   ++kk)
    for(auto jj=1;  jj<=n;   ++jj)
        for (auto i = 1; i <= b; ++i  ){
            for (auto k = 1; k<= b; ++k) {
                for (auto j = 1; j<= b; ++j){
                        C((ii-1)*b + i, (kk-1)*b + k) += A((ii-1)*b + i, (jj-1)*b + j) * B((jj-1)*b + j, (kk-1)*b + k);
                }
            }
        }
        
}


    
  
