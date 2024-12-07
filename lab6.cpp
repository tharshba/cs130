// Crypto Lab
// COSC130
// When given an encrypted file, a data key, and an index key, the program decodes the file and prints the message
// Taegun Harshbarger
// 10-09-2020
// Gregory Croisdale, Preston Provins, and Chris Muncey's Guide

#include <cstdio>
using namespace std;

struct block {
	char data; 
	char padding[3];
	int index;
};


int main (int argc, char** argv) {
	FILE* fl;

	if (argc < 4) {
		printf("Usage: (filename) (dkey) (nkey)\n"); //Prints if the user uses the wrong format in the command line
		return (1);
	}

	fl = fopen(argv[1],"rb"); //Opens the file for reading in binary

	if (fl == nullptr) {
		perror(argv[1]); //Prints an error if the file cannot be opened
		return (1);
	}

	int fileSize;

	fseek(fl, 0, SEEK_END); //These 3 lines find the size of the file by seeking to the end and using ftell
	fileSize = ftell(fl);
	fseek(fl, 0, SEEK_SET);

	int n_blocks = fileSize/8;	//Blocks would be the #of bits/8

	block* blocks = new block[n_blocks]; //Creates an object of type block
	fread (blocks, sizeof(block), n_blocks, fl); //Since the file is opened in binary, this is able to read the file straight into blocks

	fclose(fl); //Closes the file

	char* out = new char[n_blocks]; //Creates a char array to store the decrypted data in
	int placement; //Used to find the place each letter goes into
	
	int nkey;
	
	sscanf(argv[3],"%d", &nkey); //This passes the commandline argument 3 to an int labeled as nkey for index key

	for(int i=0; i < n_blocks; i++) { //Runs until there are no more blocks
		placement = blocks[i].index ^ nkey; //XOR blocks index with the nkey to find the placement of that block
		out[placement] = (blocks[i].data ^ *argv[2]); //XOR the blocks data with the commandline aregument 2 (the dkey) to find the actual data stored there
		if (placement > n_blocks) {
			printf("Error decoding chunk %d, decoded index %d, but max chunk is %d", i, placement, n_blocks); //Checks the placement to make sure it is possible and does not exceed the number of bytes
			return(-1);
			}	
	}

	printf("%s", out); //Prints the decoded statement






delete[] blocks; //Deletes the blocks
delete[] out; //Deletes the out
return(0);
}




