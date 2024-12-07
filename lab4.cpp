// Floating-point Arithmetic Lab
// COSC130
// This lab will take a float and add or multiply it using IEE-754 format
// Taegun Harshbarger
// 09-25-20
// Gregory Croisdale, Preston Provins, and Chris Muncey's Guide

#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Real
{
	//sign bit
	int sign;

	//UNBIASED exponent
	long exponent;

	//Fraction including implied 1 at bit index 23
	unsigned long fraction;
};

Real Decode(int);
int  Encode(Real);
Real Normalize(Real);
Real Multiply(Real, Real);
Real Add(Real, Real);

int main(int argc, char** argv)
{
	Real rLeft, rRight, result;
	int left, right, value;
	float l, r, v;
	char op;

	if (argc < 4)
	{
		fprintf(stderr, "Usage: %s <left> <op> <right>\n", argv[0]);
		return -1;
	}

	sscanf(argv[1], "%f", (float *)&left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%f", (float *)&right);

	printf("0x%08x %c 0x%08x\n", left, op, right);

	rLeft  = Decode(left);
	rRight = Decode(right);

	switch(op)
	{
		case 'x':
			result = Multiply(rLeft, rRight);
			break;
		case '+':
			result = Add(rLeft, rRight);
			break;
		default:
			printf("Unknown operator '%c'\n", op);
			return -2;
	}

	value = Encode(result);
	l = *(float*)&left;
	r = *(float*)&right;
	v = *(float*)&value;
	printf("%.3f %c %.3f = %.3f (0x%08x)\n", l, op, r, v, value);

	return 0;
}

Real Decode(int val)
{
Real out;

	out.sign      = (val >> 31) & 0x1; //This finds the sign by finding the bit that indicates sign
	out.exponent  = (val >> 23) & 0xff; //This finds the exponent by moving the bits to the right until the 8 exponent bits are at the front of the value. It then is & with 0xff to mask it
	out.exponent = out.exponent - 127; //Subtracts the constant from the exponent value finding the true value
	out.fraction  = (1 << 23) | ((val) & 0x7fffff); //This will isolate the bits after the exponent and add the implied 1

return(out);
}

int Encode(Real r)
{
int out=0;

	out        = out | (r.sign << 31); //Moves the value of the sign to the left most bit
	r.exponent = r.exponent + 127; //Adds the constant to the exponent value
	out        = out | ((r.exponent << 23) & 0x7fffffff); //Moves the values of the exponent left 23 bits so to put it in the right position for the IEEE-754 format
	out	       = out | ((r.fraction^(1 << 23)) & 0xfffffffff); //XORs to get rid of the implied 1 in the fraction
return(out);
}

Real Normalize(Real val)
{
Real output;
output.sign=val.sign; //Sets the sign bit
int i=23; //This is the max amount of bits after truncating in the multiplication function
int k;
	while(((val.fraction >> i) & 0x1)== 0) //Right shifts the bits by 24 incrementing down by 1 to find the first 1 in the sequence
	{
		i--;
	}	

k=23-i; //23-i allows for the right bit to be located 
	
	output.fraction=val.fraction << (k);
	output.exponent=val.exponent + (k);

return(output);
}

Real Multiply(Real left, Real right){
	Real output;

	output.sign=left.sign^right.sign; //XOR the signs to find if it is positive or negative
	output.exponent=left.exponent+right.exponent; //Add exponents
	output.fraction=((left.fraction*right.fraction)>>23); //Multiply and truncate the extra characters
	output=Normalize(output); //Normalize
return(output);
}

Real Add(Real left, Real right)
{
	Real output;

	if (left.exponent > right.exponent) //Left exponent is larger so it is a bigger number.
	{
		output.sign=left.sign; //output sign equals left sign
		output.exponent=left.exponent;
	}

	else if (left.exponent==right.exponent) //Both exponents are equal
	{ 
	
		if (left.fraction > right.fraction)	//left fraction is larger than right
		{
			output.sign=left.sign; //output equal left sign
			output.exponent=left.exponent;
		}
		
		else if (left.fraction==right.fraction) //left fraction is equal to right.
		{
			if (left.sign>right.sign) //Signs are opposite. Output 0
				{
					output.sign=0;
					output.exponent=0;
					output.fraction=0;
				}
			else 
				{
					output.sign=right.sign; //Signs are same. Output equal right sign
					output.exponent=right.exponent;
				}
		}

	}
	else //Any other case, the right would be larger than the left
	{
		output.sign=right.sign; //output equal right sign
		output.exponent=right.exponent;
	}

	if (output.sign==1)                     //Checks the sign of the inputs and uses two's complement if needed
	{
		if (left.sign==1)
		{
			left.fraction=~left.fraction+1;
		}

		else if (right.sign==1)
		{
			right.fraction=~right.fraction+1;
		}
	}
	output.exponent=output.exponent+1;
	output.fraction=((left.fraction + right.fraction)>>1); //Adds the fractions
	
//	if (output.sign==1)
//	{
//		output.fraction=~output.fraction+1;
//	}
	output=Normalize(output); //Uses the normalize function to fix the output
return(output);
}
