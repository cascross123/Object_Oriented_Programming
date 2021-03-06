#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "matrix.h"


using namespace std; //standard namespace used

double* readTXT(char *fileName, int sizeR, int sizeC); //converts the hex in the .txt file to a 1 dimensional array
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);
int main() //declares the main section
{

	int M = 512; int N = 512; //readTXT reads an image file of the defined size, and stores the result in the inputData object.


	double* shuffled_input_data = 0;
	double* noisy_input_data = 0;
	cout << endl;
	cout << "This is the data found in the file--------------------" << endl;



	char* inputFileName = "shuffled_logo.txt"; //this is the file that the image is stored in to be read. 

	shuffled_input_data = readTXT(inputFileName, M, N); 


	Matrix shuffled_matrix(M, N, shuffled_input_data); //creates a new Matrix and stores the shuffled image data in it 

	//reading in the unshuffled noisy logo
	inputFileName = "unshuffled_logo_noisy.txt";
	
	noisy_input_data = readTXT(inputFileName, M, N);
	
	Matrix noisy_matrix(M, N, noisy_input_data); //creates a new matrix and stores the noisy image in it

	Matrix output_image(M, N);

	noisy_matrix.getblock(0,31,0,31)
	
	
	for (int i = 0; i < 16*16; i++)
	
	{
		Matrix referenceblock = noisy_matrix.getblock((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31);
		Matrix tempblock = shuffled_matrix.getblock ((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31);
		
		for (int j = i+1;  j < 16*16; j++)
		
		{
			matrix testBlock = shuffledlogo.getBlock ((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31)
			
			int testSqrDiff = (referenceblock-testblock).getSS();
			int tempSqrDiff = (referenceblock-tempblock).getSS();
			
			if (testSqrDiff <= tempSqrDiff)
			
			{
				tempblock = testblock
				output_image.setblock ((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31, tempblock)
				
			}
			
		}
	
	}
	
	
	
	//block from noisy, block from shuffled, loop through shuffled, setblock
	
	//i=0 i=<16 i++
    
    shuffled_matrix.getblock(0,31,0,31)
	
	
	
	
	
	
	/* 	Here lies the code for unshuffling the image and making it work

	getBlock(int start_row, int end_row, int start_column, int end_column)

	this is where that should go, and everything below is outputting the finalised image

	*/


	char* outputFileName = "unshuffled_logo.pgm";
	/*specifies the filename that the unshuffled image will be saved to.
	Will save as a .pgm format, which can be read as a normal image*/

	int Q = 255;
	WritePGM(outputFileName, output_image.getData(), M, N, Q);

	delete[] shuffled_input_data;
	delete[] noisy_input_data; //Deletes the stored data to save on memory usage
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