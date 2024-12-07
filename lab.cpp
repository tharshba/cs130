//C Lab
//COSC130
//This lab changes the fundamental values of different characters so to use them in equations and then transform them back to characters and strings.
//Taegun Harshbarger
//8/28/2020
//Paul Preston Provins and Gregory Thomas Croisdale
#include <iostream>
#include <string>
using namespace std;

//Prototypes for the functions that you will write

int  CharToInt(char v)
{
	if (v >= '0' && v <= '9'){
		//By subtracting v by 0, I am really subtracting a char of a digit by 48. Since int 0-9 start at 0-9 on the ASCII table, this should return the integer value of the character put in.
		return(v-'0');
	}
	else {
		printf("Error in CharToInt due to an unkown character. The answer is unreliable.\n");
		return(-1);
	}
}

char IntToChar(int v)
{
	if (v >= 0 && v <= 9){
		//By adding v and the char 0, I am really adding a number and 48. This will allow me to reach the ASCII values of the char's of the digits.
		return(v+'0');
	}
	else{
		printf("Error in IntToChar\n");
		return(-1);
	}
}

int StringToInt(string val)
{
	//This function works by, first detecting whether the integer from the string is meant to be negative. It then takes the string until it reaches the end and turns it into a int value
	//From there, it will then multiply the prior number by ten everytime the CharToInt function is called. This allows the string to be turned into an int.
int i=0;
int j=0;
	if (val[0] == '-'){
		i++;
		while(val[i] != '\0'){
			j=j * 10 + (CharToInt(val[i]));
			i++;
		}	
return(-1 * j);
	}
	else{
		while(val[i] != '\0'){
			j=j * 10 + (CharToInt(val[i]));
			i++;
		}
return(j);
	}
}



string IntToString(int val)
{
	//This uses the modulo function to find the value of the single digits in the different places of the int. The value is then divided by ten and the rest of the digits are found, but it is backwards.
	//By doing this once, the end of the int can be found. I then redid the first half of the program, but put it back into the right place since the program now knows the length of the int.
	//The code also determines whether the number is negative or not and fixes the - to the string accordingly.
int copy1;
string copy2;
int k;
int i;
int val2;


if (val > 0) {
	val2=val;
	for (i=0; val > 0 || val < 0; i++){
		copy1=val%10;
		copy2[i]=IntToChar(copy1);
		val=val/10;
	} 
	k=i;
	k--;
	for (i=0; k >= 0; k--){
		copy1=val2%10;
		copy2[k]=IntToChar(copy1);
		val2=val2/10;
	}

return(copy2);}

else if(val==0){
	copy2[0]='0';
return(copy2);
	}

else {
	val=val*-1;
	val2=val;
	for (i=0; val > 0 || val < 0; i++){
		copy1=val%10;
		copy2[i]=IntToChar(copy1);
		val=val/10;
	} 
	k=i;
	for (i=0; k >= 0; k--){
		copy1=val2%10;
		copy2[k]=IntToChar(copy1);
		val2=val2/10;
	
	}
	copy2[0]='-';
return(copy2);}
   

}

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());
        return 0;
}


