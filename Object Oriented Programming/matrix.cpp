#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "Matrix.h" //includes the header file created for this project

using namespace std; //standard namespace used

double* readTXT(char *fileName, int sizeR, int sizeC); //converts the hex in the .txt file to a 1 dimensional array
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);



int main() //declares the main section
{

	int M = 512; int N = 512; //readTXT reads an image file of the defined size, and stores the result in the inputData object.


	double* input_data = 0;

	cout << endl;
	cout << "This is the data found in the file--------------------" << endl;

	char* inputFileName = "shuffled_logo.txt"; //this is the file that the image is stored in to be read. 
	input_data = readTXT(inputFileName, M, N);



	
	/* 	Here lies the code for unshuffling the image and making it work

	this is where that should go, and everything below is outputting the finalised image

	*/


	char* outputFileName = "logo_restored.pgm";
	/*specifies the filename that the unshuffled image will be saved to.
	Will save as a .pgm format, whcih can be read as a normal image*/

	int Q = 255;
	WritePGM(outputFileName, input_data, M, N, Q);

	delete[] input_data; //Deletes the stored data to save on memory usage
	cout << "the image has finished processing" << endl;
	getchar(); //means the program will not close after the data has finished processing, so that any errors can be seen by the user. 

	return 0; //reset

}

double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())

	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break; //basically stops the program when it stops seeing the image. 
			myfile >> *(data + i);
			//cout << *(data + i) << '.'; //outputs the data to the console window so you can see what is happeneing. good for debugging but messes with your eyes
			i++;
		}
		myfile.close();
	}
	else cout << "could not open file";

	return data;
}






// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}



Matrix::Matrix()
{
	_M = 1;
	_N = 1;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = 0;
	}

}

Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	_M = sizeR;
	_N = sizeC;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = input_data[x];
	}
}
//copy constructor
Matrix::Matrix(const Matrix& m)
{
	std::cout << "copy constructor" << std::endl;
	_M = m._M;
	_N = m._N;

	_data = new double[_M*_N];

	for (int i = 0; i < _M*_N; i++)
	{
		_data[i] = m._data[i];
	}
}

//operator overloads
Matrix Matrix::operator+(const Matrix& other)
{
	std::cout << "Operator '+' overload" << std::endl;
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] + other._data[x];
	}

	return temp;
}

Matrix Matrix::operator=(const Matrix& other)
{
	std::cout << "Operator '=' overload" << std::endl;
	//delete existing _data information - as we are going to replace it with 'other._data'
	delete[] _data;
	_M = other._M;
	_N = other._N;

	//reserve memory for new array
	_data = new double[_M*_N];

	//'this' pointer refers to the current object
	for (int x = 0; x < (_M*_N); x++)
	{
		this->_data[x] = other._data[x];
	}

	return *this;
}


//functions
int Matrix::getM()
{
	return _M;
}

int Matrix::getN()
{
	return _N;
}

double Matrix::get(int i, int j)
{
	return _data[(i*_N)+j];
	
}

Matrix Matrix::getBlock(int start_row, int end_row, int start_column, int end_column)
{
	//set number of rows and columns in the subimage
	int rows = (end_row - start_row) + 1;
	int columns = (end_column - start_column) + 1;
	//reserve the memory for data extracted from the main image
	double* tempData = new double[rows*columns];

	//variable to set the new array index
	int count = 0;

	//iterate through the image data, extracting the values according to the rows/columns
	for (int x = start_row; x < (rows+start_row); x++)
	{
		for (int y = start_column; y < (columns+start_column); y++)
		{
			tempData[count] = get(x, y);
			count++;
		}
	}

	//create a temporary matrix based on the row/column/data extracted
	Matrix temp(rows, columns, tempData);
	//delete the heap memory reserved for the extracted data
	delete[] tempData;

	//return the temporary matrix
	return temp;
}

Matrix Matrix::add(const Matrix& other)
{
	//create temporary array of row*colum size
	double* data = new double[other._M*other._N];

	//fill the array with other._data
	for (int x = 0; x < (other._M*other._N); x++)
	{
		data[x] = this->_data[x] + other._data[x];
	}

	//create a temporary Matrix object with the row/column/data info
	Matrix temp(other._M, other._N, data);
	//delete the data array (which we can do as the array is 'deep copied' when 'temp' is created
	delete[] data;

	return temp;

}

double* Matrix::getData()
{
	return _data;
}




Matrix::~Matrix()
{
	std::cout << "Destructor" << std::endl;
	delete [] _data;
}
