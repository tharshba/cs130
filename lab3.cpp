// Binary Arithmetic Lab
// COSC130
// This lab will be making functions that act as the simple notation of add, subtract, multiply, and divide without using any of mathematical notation, only bitwise operators.
// Taegun Harshbarger
// 09-18-20
// Paul Preston Provins, Gregory Thomas Croisdale, and Chris Muncey's Guides

#include <iostream>
using namespace std;

int Multiply(int, int);
int Add(int, int);
int Sub(int, int);
int Twos(int);
int Div(int, int);

int main()
{
	int left, right, result;
	char op;

	cout << "Enter left <op> right: ";
	cin >> left >> op >> right;

	switch(op)
	{
		case 'm':
		case 'x':
		case '*':
			result = Multiply(left, right);
			break;
		case 'a':
		case '+':
			result = Add(left, right);
			break;
		case 's':
		case '-':
			result = Sub(left, right);
			break;
		case 'd':
		case '/':
			//EXTRA CREDIT ONLY!
			result = Div(left, right);
			break;
		default:
result = -11111111;
			break;
	}

	cout << "Result = " << result << endl;
	return 0;
}

int Multiply(int leftop, int rightop)
{
int leftopCopy=leftop;
int rightopCopy=rightop;

	if(((rightop >> 31) & 1)==1){ //Checks the last bit to see if the sign is positive or negative
		rightop=Sub(0,rightop);}
	else if ((leftop >> 31 & 1)==1){ //Checks the last bit to find the sign
		leftop=Sub(0,leftop);}
int product=0;
	for (int i=0; i <32; i++){ //This for loop goes through every bit of the int.
		if ((rightop & 1)==1){ //This makes sure that we add leftop to itself again. If it were zero, we would not need to add it.
			product=Add(leftop,product); //This adds the leftop to the product so to keep going to get the final product.
		}
	leftop=leftop << 1;
	rightop=rightop >> 1;
}
	if ((((leftopCopy >> 31) & 1)==0) && (((rightopCopy >> 31) &1) ==0)){ //This checks the sign bit to see if it is positive or negative 
		return(product);}
	else {return(Sub(0,product));}


} 
int Add(int leftop, int rightop)
{
int c=0;
for (int i=0; i<32; i++){ //This for loop makes sure that it goes through every bit of the int.
	c= leftop & rightop; //This sets the carry for the adding of the two functions. Anding allows the carry to be found through bitwise functions. In the case of 15+15, this would be 1111
	leftop= leftop ^ rightop; //This allows for the sum value to be found. 0000
	rightop = c << 1; //This fixes the carry value for the next iteration by shifting it left 1. 11110 which is 30.
}
return(leftop);
}

int Sub(int leftop, int rightop)
{
return(Add(leftop,Twos(rightop)));//Since subtraction is just addition with a negative number, you just add the leftop with the twos complement of the right op.
}

int Twos(int op)
{
int twos = Add(~op,1); //This finds the two's complement and adds 1 using the add function.
return(twos);
}

int Div(int leftop, int rightop)
{
	(void)leftop;
	(void)rightop;
return(0);
}
