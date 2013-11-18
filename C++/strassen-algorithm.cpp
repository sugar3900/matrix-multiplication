#include <vector>
#include <iostream>
using namespace std;


void add( vector< vector<int> >& A, vector< vector<int> >& B, vector< vector<int> >& C, int n ) {
	for ( int i = 0; i < n; i++ ) {
		for ( int j = 0; j < n; j++ ) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}
void subtract( vector< vector<int> >& A, vector< vector<int> >& B, vector< vector<int> >& C, int n ) {
	for ( int i = 0; i < n; i++ ) {
		for ( int j = 0; j < n; j++ ) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}
void printMatrix( vector< vector<int> >& m, int n ) {
	for ( int i=0;    i < n;  i++ ) {
         for( int j=0;    j < n;    j++ ) {
              cout << m[i][j] << " ";
		 }
		 cout << endl;
	}
}





void strassenAlgorithm(  vector< vector<int> >& A, vector< vector<int> >& B, vector< vector<int> >& C, int n ) {
	
	if ( n <= 1 ) return;

	//initialize everything ahead of time
	int halfn = n/2;
	vector<int> cols( halfn );
	vector< vector<int> > A00(halfn,cols), A01(halfn,cols), A10(halfn,cols), A11(halfn,cols), 
		B00(halfn,cols), B01(halfn,cols), B10(halfn,cols), B11(halfn,cols),
		C00(halfn,cols), C01(halfn,cols), C10(halfn,cols), C11(halfn,cols),
		p1(halfn,cols), p2(halfn,cols), p3(halfn,cols), p4(halfn,cols), p5(halfn,cols), p6(halfn,cols), p7(halfn,cols),
		aResult(halfn,cols), bResult(halfn,cols),
		pResult(halfn,cols), anotherpResult(halfn,cols);



	//make 4 submatrices of A and B
	for (int i = 0; i < halfn; i++) {
		for (int j = 0; j < halfn; j++) {
			A00[i][j] = A[i][j];
			A01[i][j] = A[i][j + halfn];
			A10[i][j] = A[i + halfn][j];
			A11[i][j] = A[i + halfn][j + halfn];
  
			B00[i][j] = B[i][j];
			B01[i][j] = B[i][j + halfn];
			B10[i][j] = B[i + halfn][j];
			B11[i][j] = B[i + halfn][j + halfn];
			}
	}

	
	add(A00, A11, aResult, halfn);
    add(B00, B11, bResult, halfn);
    strassenAlgorithm(aResult, bResult, p1, halfn);
  
    add(A10, A11, aResult, halfn); 
    strassenAlgorithm(aResult, B00, p2, halfn); 
  
    subtract(B01, B11, bResult, halfn); 
    strassenAlgorithm(A00, bResult, p3, halfn); 
  
    subtract(B10, B00, bResult, halfn);
    strassenAlgorithm(A11, bResult, p4, halfn); 
  
    add(A00, A01, aResult, halfn); 
    strassenAlgorithm(aResult, B11, p5, halfn);   
  
    subtract(A10, A00, aResult, halfn); 
    add(B00, B01, bResult, halfn); 
    strassenAlgorithm(aResult, bResult, p6, halfn);
  
    subtract(A01, A11, aResult, halfn); 
    add(B10, B11, bResult, halfn); 
    strassenAlgorithm(aResult, bResult, p7, halfn); 



	//find 4 submatrices of C
	add( p5, p4, pResult, halfn );
	subtract( pResult, p2, anotherpResult, halfn );
	add( anotherpResult, p6, C00, halfn );

	add( p1, p2, C01, halfn );

	add( p3, p4, C10, halfn );

	add( p1, p5, pResult, halfn );
	subtract( pResult, p3, anotherpResult, halfn );
	subtract( anotherpResult, p7, C11, halfn );



	//make C
	for (int i = 0; i < halfn ; i++) {
		for (int j = 0 ; j < halfn ; j++) {
			C[i][j] = C00[i][j];
			C[i][j + halfn] = C01[i][j];
			C[i + halfn][j] = C10[i][j];
			C[i + halfn][j + halfn] = C11[i][j];
		}
	}
	


}


int main() {

	int n = 10;
	vector<int> cols (n, 0);
    vector< vector<int> > A(n, cols), B(n, cols), C(n, cols);

	strassenAlgorithm(A, B, C, n);
    printMatrix(C,n);
  
	cin.get();
}
