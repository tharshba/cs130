// Disassembler Lab
// COSC130
// This lab will take machine code and produce assembly code in the RISC-V Architecture
// Taegun Harshbarger
// 10-29-2020
// Gregory Croisdale, Preston Provins, and Chris Muncey's Guide
#include <stdlib.h>
#include <stdio.h>
#include <string>

int main(int argc, char** argv)
{

	if (argc < 3) {
		printf("Not enough arguments"); //Makes sure there are enough arguments for the program to function correctly
		exit(EXIT_FAILURE);	
	}
	else if (argc > 4){
		printf("Too many arguments");  //Makes sure there are not too many arguments for the program to function
		exit(EXIT_FAILURE);
	}
	char abi = 'a';
	if (argc == 4) {
		abi = argv[3][0]; //Sets the abi
	}

	FILE* flin;
	FILE* flout;

	flin = fopen(argv[1],"rb"); //Opens the input file

	if (flin == nullptr) { //Error checks the input file
		perror(argv[1]);
		return(1);
	}

	int fileSize;

	fseek(flin, 0, SEEK_END);
	fileSize = ftell(flin)/4; //Finds the number of instructions that will need to be converted
	fseek(flin, 0, SEEK_SET);

	int *myData = new int[fileSize]; //Creates the int array myData

	fread(myData, fileSize * sizeof(int), 1, flin); //Reads the file into the int array myData
	fclose(flin);
	flout = fopen(argv[2], "wt");
	int opCodeMask = 0x7F; //Mask for the opCode

	for (int i=0; i < fileSize; ++i) { //This loop goes through every instruction in the file
		int iTypeFamilyCheck = 0x13; //Bitmask to check if it is in the i-type family
		int iTypeRD = (0x1F << 7);   //This is a bitmask to find the iTypeRD
		int iFunc = (0x7 << 12);     //Bitmask to find the iTypeFunc code so the name can be subsequently deduced
		int iTypeRS = (0x1F << 15);  //This is a bitmask to find the iTyperRS
		int iTypeImmediate = (0xFFF << 20); //Bitmask to find the immedatie in the i-type

		int rTypeFamilyCheck = 0x33; //Masks for the r-type
		int rTypeRD = (0x1F << 7);
		int rFunc = (0x7 << 12);
		int rTypeRS1 = (0x1F << 15);
		int rTypeRS2 = (0x1F << 20);
		int rFunc7 = (0x7F << 25);

		int sTypeFamilyCheck = 0x23; //Masks for the s-type
		int sTypeImmediate1 = (0x1F << 7);
		int sFunc = (0x7 << 12);
		int sTypeRS1 = (0x1F << 15);
		int sTypeRS2 = (0x1F << 20);
		int sTypeImmediate2 = (0x7F << 25);

		int uTypeFamilyCheck = 0x37; //Masks for the u-type
		int uTypeRD = (0x1F << 7);
		int uTypeImmediate = (0xFFFFF << 12);

		int jTypeFamilyCheck = 0x6f; //Masks for the j-type
		int jTypeRD = (0x1F << 7);
		int jTypeImmediate3 = (0xFF << 12);
		int jTypeImmediate2 = (0x1 << 20);
		int jTypeImmediate1 = (0x3FF << 21);
		int jTypeImmediate4 = (0x1 << 31);

		int iTypeFamilyCheck64 = 0x03; //Masks for the 64bit i-type does not work
		int iTypeRD64 = (0x1F << 7);  
		int iFunc64 = (0x7 << 12);    
		int iTypeRS64 = (0x1F << 15); 
		int iTypeImmediate64 = (0xFFF << 20);

		int rd = 0;
		int rs = 0;
		int rs1 = 0;
		int rs2 = 0;
		int func7 = 0;
		int imm = 0;
		int imm1 = 0;
		int imm2 = 0;
		int func = 0;

		int retrievedCode = myData[i] & opCodeMask; //&s myData and opCodeMask to find the opCode
		std::string instr = "inv";
		if (retrievedCode == iTypeFamilyCheck) { //Makes sure the code is of the iTypeFamily
			func = myData[i] & iFunc; //Puts the function data into iFunc
			func = (func >> 12); //Moves func back to the first few bits so that it can be compared easier
			if (func == 0x0) {
				instr = "addi";
			}
			else if (func == 0x3) {
				instr = "sltiu";
			}
			else if (func == 0x7) {
				instr = "andi";
			}
			else if (func == 0x2) {
				instr = "slti";
			}

			else if (func == 0x4) {
				instr = "xori";
			}

			else if (func == 0x6) {
				instr = "ori";
			}
			rd = (myData[i] & iTypeRD) >> 7; //Moves the different values back to the first few bits so that they can be printed
			rs = (myData[i] & iTypeRS) >> 15;
			imm = (myData[i] & iTypeImmediate) >> 20;

			fprintf(flout, "     %-6.6s x%d, x%d, %d //0x%-8.08x\n", instr.c_str(), rd, rs, imm, myData[i]);
		}

		if (retrievedCode == iTypeFamilyCheck64) { //Makes sure the code is of the 64iTypeFamily
			func = myData[i] & iFunc64; //Puts the function data into 64iFunc
			func = (func >> 12); //Moves func back to the first few bits so that it can be compared easier
			if (func == 0x6) {
				instr = "lwu";
			}
			else if (func == 0x5) {
				instr = "ld";
			}
			rd = (myData[i] & iTypeRD64) >> 7; //Moves the different values back to the first few bits so that they can be printed
			rs = (myData[i] & iTypeRS64) >> 15;
			imm = (myData[i] & iTypeImmediate64) >> 20;

			fprintf(flout,"     %-6.6s x%d, x%d, %d //0x%-8.08x\n", instr.c_str(), rd, rs, imm, myData[i]);
		}

			if (retrievedCode == rTypeFamilyCheck) { //Makes sure the code is of the rTypeFamily
			func = myData[i] & rFunc; //Puts the function data into rFunc
			func = (func >> 12); //Moves func back to the first few bits so that it can be compared easier
			func7 = myData[i] & rFunc7;
			func7 = (func7 >> 25); //Have to move the func7 element to the first few bits so it can be compared
			if ((func == 0x0) && (func7 == 0x00)) { 
				instr = "add";
			}
			else if ((func == 0x00) && (func7 == 0x20)) {
				instr = "sub";
			}
			else if (func == 0x1) {
				instr = "sll";
			}
			else if (func == 0x2) {
				instr = "slt";
			}
			else if (func == 0x3) {
				instr = "sltu";
			}

			else if (func == 0x4) {
				instr = "xor";
			}

			else if (func == 0x5 && func7 == 0x00) {
				instr = "srl";
			}

			else if (func == 0x5 && func7 == 0x20) {
				instr = "sra";
			}
			else if (func == 0x6) {
				instr = "or";
			}
			else if (func == 0x7) {
				instr = "and";
			}
				
			rd = (myData[i] & rTypeRD) >> 7; //Moves the different values back to the first few bits so that they can be printed
			rs1 = (myData[i] & rTypeRS1) >> 15;
			rs2 = (myData[i] & rTypeRS2) >> 20;
			
			fprintf(flout,"     %-6.6s x%d, x%d, x%d //0x%-8.08x\n", instr.c_str(), rd, rs1, rs2, myData[i]);
		}

	if (retrievedCode == sTypeFamilyCheck) { //Makes sure the code is of the sTypeFamily
			func = myData[i] & sFunc; //Puts the function data into sFunc
			func = (func >> 12); //Moves func back to the first few bits so that it can be compared easier
			if (func == 0x0) {
				instr = "sb";
			}
			else if (func == 0x1) {
				instr = "sh";
			}
			else if (func == 0x2) {
				instr = "sw";
			}
			imm = (((myData[i] & sTypeImmediate1) >> 7) | ((myData[i] & sTypeImmediate2) >> 20)); //Adds the immediates together to get the final immediate
			rs1 = (myData[i] & sTypeRS1) >> 15;
			rs2 = (myData[i] & sTypeRS2) >> 20;
		

			fprintf(flout,"     %-6.6s x%d, %d(x%d) //0x%-8.08x\n", instr.c_str(), rs2, imm, rs1, myData[i]);
		
		}

	if (retrievedCode == uTypeFamilyCheck) { //Makes sure the code is of the sTypeFamily
			imm = (myData[i] & uTypeImmediate); //&s the immediate and myData to get the immediate
			rd = (myData[i] & uTypeRD) >> 7; 
			instr = "lui";
			fprintf(flout,"     %-6.6s x%d, %d //0x%-8.08x\n", instr.c_str(), rd, imm, myData[i]);
		
		}

	if (retrievedCode == jTypeFamilyCheck) { //Makes sure the code is of the jTypeFamily
			imm = (((myData[i] & jTypeImmediate1) >> 21) | ((myData[i] & jTypeImmediate2) >> 20) | ((myData[i] & jTypeImmediate3) >> 12) | ((myData[i] & jTypeImmediate4) >> 31)) << 6;// Does not work
			rd = (myData[i] & jTypeRD) >> 7;
			instr = "jal";
			fprintf(flout,"     %-6.6s x%d, %d //0x%-8.08x\n", instr.c_str(), rd, imm, myData[i]);
			//Does not work properly		
		}

	}






	fclose(flout);
	delete myData; 

	return(0);
}
