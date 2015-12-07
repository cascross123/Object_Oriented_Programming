#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "Matrix.h" //includes the header file created for this project

using namespace std; //standard namespace used

double* readTXT(char *flieName, int sizeR, int sizeC) //converts the hex in the .txt file to a 1 dimensional array
void WritePGM(char *filename, double *data, int sizeR, int sizeC,intQ);

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
				myfine >> *(data + i);
				cout << *(data + i) << ''; //outputs the data to the console window so you can see what is happeneing. good for debugging but messes with your eyes
				i++;
			}
			myfile.close();
		}
		else cout << "could not open file";
		
		return data;
}
				
	
}