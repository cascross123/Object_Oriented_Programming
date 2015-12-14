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
	Will save as a .pgm format, which can be read as a normal image*/

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