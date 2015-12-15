#pragma once
#pragma once

class Matrix

{



private:

	int _M, _N;

	double *_data;



public:

	Matrix();

	Matrix(int M, int N);

	Matrix(int sizeR, int sizeC, double* input_data);

	//copy constructor

	Matrix(const Matrix& m);

	//operator overloads

	Matrix operator+(const Matrix& other);

	Matrix operator=(const Matrix& other);
	//functions

	int getM();

	int getN();

	double get(int i, int j);

	Matrix getBlock(int startR, int endR, int startC, int endC);

	Matrix add(const Matrix& other);

	double* getData();

	~Matrix();

};


/*
//create output logo matrix

//get block
write for loop 
loop each tile in noisy, create block


temp block from noisy image
test block from shuffled image
set block

if temp < test 

{

tempBlock = testBlock

}

output logo.setblock (tempblock);
*/