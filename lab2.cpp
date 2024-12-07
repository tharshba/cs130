//BitSet Lab
//COSC130
//Explain Lab Here
//Taegun Harshbarger
//8/28/2020
//Paul Preston Provins and Gregory Thomas Croisdale

#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

class BITSET {
	private:
		vector <int> bits;
	public:
		BITSET();
		bool Test(int);
		void Set(int);
		void Clear(int);

		int GetNumSets();
		int GetSet(int);
};

BITSET::BITSET() {
	bits.resize(1,0);}

bool BITSET::Test(int number)
{ //Number is 40 and bits is 32 bits
	number=40;
	int setNum;
	setNum=number/32; //This will find that setNum is 1
	number=number%32; //This will find the remainder of values needed to cross that is 9
		if (1 == ((bits[setNum] >> number) & 1)) {

			return(1);}

		else { //Else will be triggered because the 1st set does not exist yet in this instance
			return(0);}
}
void BITSET::Set(int number)
{ //Number is 40 and bits is only 32 bits
	int setNum;
	int size;
	size=bits.size();
	setNum=number/32; //setNum=1
		if ((size) < (setNum+1)){ //If the size of the vector is less than the setNum+1 than we need to reset the size of the vector
			bits.resize(setNum, 0); //resizes bits to be 2 int long
			number=number%32; //Finds the remainder which is 9
			bits[setNum] |= (1 << number);} //This will set the 2nd int in the bits vector to 1 by ORing it with a mask of the integer one left shifted to be in the correct position
		else { //If the size of the vector is equal to or more than the setNum+1 than the vector does not need to be resized.
			number=number%32; 
			bits[setNum] |= (1 << number);}
}

void BITSET::Clear(int number)
{ //number is 40
	int setNum;
	int size;
	size=bits.size();
	setNum=number/32; //setNum=1
		if ((size) >= (setNum+1)){ //Makes sure space is not wasted if the vectors does not have values in that int
			number=number%32; //Finds the remainder which is 9
			bits[setNum] = bits[setNum] & ~(1 << number);
					while (bits[size-1]==0) {
						bits.erase(bits.begin() + (size-1));
						size--;
					}
		}

		else{}
}

int BITSET::GetNumSets()
{
	return(bits.size());
}

int BITSET::GetSet(int number)
{
	int size;
	size=bits.size();
		if(size-1 <= number) {
			return(bits[number]);
			}
		else {
			return(0);
		}
}

string ToBinary(int, int)
{
return(0);
}


int main(int argc, char *argv[]){
printf("Please pick a command\n t <bit> - Prints 1 or 0 depending on if the given bit # is 1 or 0.\n s <bit> - Sets the given bit to 1.\n c <bit> - Clears the given bit to 0.\n g <set> - Prints the binary representation of the given set.\n n - Prints the number of sets in the bitset. This will always be at least 1.\n q - Quits and returns to the console\n Enter command:\n");
	BITSET bit;
	int number;
	char functionSelect= 'r';
	int binary;
	
		if (3 != argc) {
				printf("Usage: <command> <bit>\n");
				return(-1);}
		while (functionSelect != 'q'); {
		fgets(argv[1],1,stdin);
		fgets(argv[2],1,stdin);
		functionSelect = argv[1][0];
		number = atoi(argv[2]);
		number=1;
		binary=(bit.Test(number));
		printf("%i", binary);
		binary=(bit.GetNumSets());
		printf("%i", binary);
		switch (functionSelect) 
			{
				case 't':
					binary=(bit.Test(number));
					printf("%i", binary);
					break;
				case 's':
					bit.Set(number);
					break;
				case 'c': 
					bit.Clear(number);
					break;
				case 'g':
					bit.GetSet(number);
					break;
				case 'n':
					bit.GetNumSets();
					break;
				case 'q':
					exit(0);
					break;
			}
		
		}
return(0);
}

