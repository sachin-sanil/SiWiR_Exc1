#include <iostream>
#include <vector>

void naivemult(matrix& A, matrix& B, matrix& C)
{    
    assert((A.cols == B.rows) && (A.rows == C.rows) && (B.cols == C.cols));
    int p = A.rows;
    int q = A.cols;
    int r = C.cols;
    double s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16;
 if (!(q%8 == 0)) {
    for (auto i = 1; i <= p; ++i  ){
    	for (auto k = 1; k<= r; ++k) {
		s1 = 0;
		s2 = 0;
		s3 = 0;
		s4 = 0;
		s5 = 0;
		s6 = 0;
		s7 = 0;
		s8 = 0;
		s9 = 0;
                s10 = 0;
                s11= 0;
                s12 = 0;
                s13 = 0;
                s14 = 0;
                s15 = 0;
                s16 = 0;

    		for (auto j = 1; j<= q; j=j+16){

        	    s1 += A(i,j) * B(j,k);
		    s2 += A(i,j+1) * B(j+1,k);
		    s3 += A(i,j+2) * B(j+2,k);
		    s4 += A(i,j+3) * B(j+3,k);
		    s5 += A(i,j+4) * B(j+4,k);
		    s6 += A(i,j+5) * B(j+5,k);
		    s7 += A(i,j+6) * B(j+6,k);
		    s8 += A(i,j+7) * B(j+7,k);	
			s9 += A(i,j+8) * B(j+8,k);
                    s10 += A(i,j+9) * B(j+9,k);
                    s11 += A(i,j+10) * B(j+10,k);
                    s12 += A(i,j+11) * B(j+11,k);
                    s13 += A(i,j+12) * B(j+12,k);
                    s14 += A(i,j+13) * B(j+13,k);
                    s15 += A(i,j+14) * B(j+14,k);
                    s16 += A(i,j+15) * B(j+15,k);
		   // C(i,k) += s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8;		

    		} C(i,k) = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10 + s11 + s12 + s13 + s14 + s15 + s16;
   	 }
    }
 }
 else {
    for (auto i = 1; i <= p; ++i  ){
        for (auto k = 1; k<= r; ++k) {
                for (auto j = 1; j<= q; ++j){

            C(i,k) += A(i,j) * B(j,k);
                }
    }
 }
}
}

void multiply(matrix& A, matrix& B, matrix& C)
{
  
    int p = A.rows;
    int q = A.cols;
    int r = C.cols;
    
    assert((A.cols == B.rows) && (A.rows == C.rows) && (B.cols == C.cols));
    int b = 32;
    if (!(A.cols == A.rows && B.rows == B.cols && A.cols%b==0))
        b = 1;
    
    p = A.rows/b;
    q = A.cols/b;
    r = C.cols/b;

      
    double s1,s2,s3,s4,s5,s6,s7,s8;

 if (q%8 == 0) {
    for(auto ii=1;  ii<=p;   ++ii)
    for(auto kk=1;  kk<=q;   ++kk)
    for(auto jj=1;  jj<=r;   ++jj)
        for (auto i = 1; i <= b; ++i  ){
            for (auto k = 1; k<= b; ++k) {
			 s1 = 0;
                s2 = 0;
                s3 = 0;
                s4 = 0;
                s5 = 0;
                s6 = 0;
                s7 = 0;
                s8 = 0;

                for (auto j = 1; j<= b; j=j+8){
			s1 += A((ii-1)*b + i, (jj-1)*b + j) * B((jj-1)*b + j, (kk-1)*b + k);
			s2 += A((ii-1)*b + i, (jj-1)*b + j+1) * B((jj-1)*b + j+1, (kk-1)*b + k);
			s3 += A((ii-1)*b + i, (jj-1)*b + j+2) * B((jj-1)*b + j+2, (kk-1)*b + k);
			s4 += A((ii-1)*b + i, (jj-1)*b + j+3) * B((jj-1)*b + j+3, (kk-1)*b + k);
			s5 += A((ii-1)*b + i, (jj-1)*b + j+4) * B((jj-1)*b + j+4, (kk-1)*b + k);
			s6 += A((ii-1)*b + i, (jj-1)*b + j+5) * B((jj-1)*b + j+5, (kk-1)*b + k);
			s7 += A((ii-1)*b + i, (jj-1)*b + j+6) * B((jj-1)*b + j+6, (kk-1)*b + k);
			s8 += A((ii-1)*b + i, (jj-1)*b + j+7) * B((jj-1)*b + j+7, (kk-1)*b + k);
                        
			//C((ii-1)*b + i, (kk-1)*b + k) += s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8;
                }C((ii-1)*b + i, (kk-1)*b + k) = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8;
            }
        }
    }
    else
    {
	for(auto ii=1;  ii<=p;   ++ii)
	    for(auto kk=1;  kk<=q;   ++kk)
	        for(auto jj=1;  jj<=r;   ++jj)
	           for (auto i = 1; i <= b; ++i  ){
	              for (auto k = 1; k<= b; ++k) {
                         for (auto j = 1; j<= b; ++j){
	                     C((ii-1)*b + i, (kk-1)*b + k) += A((ii-1)*b + i, (jj-1)*b + j) * B((jj-1)*b + j, (kk-1)*b + k);
	                 }
	              }
	        }
    }
}


    
  
