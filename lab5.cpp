// C-Files Lab
// COSC130
// This lab will take a file and run a MUD using it
// Taegun Harshbarger
// 10-02-2020
// Gregory Croisdale, Preston Provins, and Chris Muncey's Guide

#include<cstdio>
#include<cstring>
#include<string>

int main(int argc,char *argv[]) {

if (argc > 2) {
		printf("Too many arguments, format should be :: ./lab <FILENAME>"); //Checks the input line
		return(-1);
	}
	else if (argc < 2) {
		printf("Too few arguments, format should be :: .lab <FILENAME>"); //Checks the input line
		return(-1);
	}
	
	FILE *fl;
	fl = fopen(argv[1],"r"); //Opens the file to be read

	if (nullptr == fl){
	perror("File was not opened successfully"); //Checks to make sure the file was opened successfully
	return(-1);
	}

	size_t numBytes = 0;
	char *fileStr = NULL;
	int tildeCount = 0;
	char *myStr;
	int i=0;
	int j=0;
	fseek(fl, 0, SEEK_END);
	int flLength;
	
	flLength = ftell(fl);
	myStr = (char *) malloc (flLength); //This allocates memory to the string 
	fseek(fl, 0, SEEK_SET);	

	while (getline(&fileStr, &numBytes, fl) > 0) {
		if(fileStr[0] == '~'){
			++tildeCount; //Counts the number of tilde to find the room number
		}
		i = 0;
		while (fileStr[i] != '\n'){
			myStr[j] = fileStr[i]; //Copies the file into a string
			++j;
			++i;
		}

	}
	int roomCount = tildeCount/3;
	

//ALLOCATE MEM FOR CSTRINGS

	//[roomCount][flLength]

	char ** roomTitle = new char*[roomCount]; //Allocates memory for the title cstring
	for(i=0; i < roomCount; i++) {
		roomTitle[i] = new char[flLength];
	}

	char ** roomDesc = new char*[roomCount]; //Allocates memory for the description cstring
	for(i=0; i < roomCount; i++) {
		roomDesc[i] = new char[flLength];
	}

	char ** roomDirec = new char*[roomCount]; //Allocates memory for the direction cstring
	for(i=0; i < roomCount; i++) {
		roomDirec[i] = new char[flLength];
	}


	fclose(fl);
	i=0;
	j=0;
	int k=0;
	
	for (k=0; k < roomCount; k++) {
		while (myStr[i] != '~') {
			(roomTitle[k][j])=myStr[i]; //Copies the room title to a cstring
			i++;
			j++;
		}
		i++;
		j=0;
		while (myStr[i] != '~') {
			(roomDesc[k][j])=myStr[i]; //Copies the room description to a cstring
			i++;
			j++;
		}
		i++;
		j=0;
		while (myStr[i] != '~') {
			roomDirec[k][j]=myStr[i]; //Copies the room directions to a cstring
			i++;
			j++;
		}
		i++;
		j=0;
	}


	int count = 0;
	char userInput;
	char direction[25][4];
	int room[25][4];
	char copy;	
	k=0;
	j=0;
	i=0;	

	while (k < roomCount) {
	count=strlen(roomDirec[k]);
			direction[k][j]=roomDirec[k][i]; //i=0
			i=i+2; //i=2
			copy=roomDirec[k][i];
			room[k][j]=((copy-'0'));
			if (roomDirec[k][i+1] >= '0' && roomDirec[k][i+1] <= '9') { //Makes it possible to have 2 digit rooms
				i++; 
				copy=roomDirec[k][i];
				room[k][j]=(room[k][j]*10)+(copy-'0');
			}

			if (count > 5 && count < 9 ) { //2 directions
				j++; //j=1
				i++; //i=3
				direction[k][j]=roomDirec[k][i];
				i=i+2; //i=5 
				copy=roomDirec[k][i];
				room[k][j]=((copy-'0'));
				if (roomDirec[k][i+1] >= '0' && roomDirec[k][i+1] <= '9') { //Makes it possible to have 2 digit rooms
					i++; 
					copy=roomDirec[k][i];
					room[k][j]=(room[k][j]*10)+(copy-'0');
				}
			}
			else if (count >= 9 && count < 12) //3 directions
			{
				while (j < 3) {
					j++; //j=1
					i++; //i=3
					direction[k][j]=roomDirec[k][i];
					i=i+2; //i=5
					copy=roomDirec[k][i];
					room[k][j]=((copy-'0'));
					if (roomDirec[k][i+1] >= '0' && roomDirec[k][i+1] < '9') {
						i++;
						copy=roomDirec[k][i];
						room[k][j]=(room[k][j]*10)+(copy-'0');
					}
				}
			}
			else if (count >= 12) //4 directions
			{
				while (j < 4) { //Loops for all cardinal directions
					j++; //j=1
					i++; //i=3
					direction[k][j]=roomDirec[k][i];
					i=i+2; //i=5
					copy=roomDirec[k][i];
					room[k][j]=((copy-'0'));
					if (roomDirec[k][i+1] >= '0' && roomDirec[k][i+1] <= '9') {
						i++;
						copy=roomDirec[k][i];
						room[k][j]=(room[k][j]*10)+(copy-'0');
					}
				}
			}
		j=0;
		i=0;
		k++;
	}


//USER STARTS PLAYING GAME

int p=0;


	while (userInput != 'q') { //Allows the player to exit the game
		printf(">");
		scanf("%s" , &userInput);
		
		
		if (userInput == 'l'){ //Allows the player to look around in the game
			printf("%s\n%s\n",roomTitle[p],roomDesc[p]);
			printf("Exits: %c %c %c %c\n", direction[p][0], direction[p][1], direction[p][2], direction[p][3]);
		}
			
		else if (userInput == 'n'){ //Allows the player to try to go north
			if (direction[p][0] == 'n') {
				p=room[p][0];
				printf("You moved North\n");
			}
			else if (direction[p][1] == 'n') {
				p=room[p][1];
				printf("You moved North\n");

			}
			else if (direction[p][2] =='n') {
				p=room[p][2];
				printf("You moved North\n");
			
			}
			else if (direction[p][3] == 'n') {
				p=room[p][3];
				printf("You moved North\n");

			}
			else {
				printf("You can't go NORTH!\n"); //Prints this if north is not an exit
			}
		}

		else if (userInput == 's'){ //Allows the player to try and move south
			if (direction[p][0] == 's') {
				p=room[p][0];
				printf("You moved South\n");
			}
			else if (direction[p][1] == 's') {
				p=room[p][1];
				printf("You moved South\n");

			}
			else if (direction[p][2] =='s') {
				p=room[p][2];
				printf("You moved South\n");

			}
			else if (direction[p][3] == 's') {
				p=room[p][3];
				printf("You moved South\n");

			}
			else {
			printf("You can't go SOUTH!\n"); //Prints the is south is not an exit
			}

		}

		else if (userInput == 'e'){ //Allows the player to move east
			if (direction[p][0] == 'e') {
				p=room[p][0];
				printf("You moved East\n");

			}
			else if (direction[p][1] == 'e') {
				p=room[p][1];
				printf("You moved East\n");

			}
			else if (direction[p][2] =='e') {
				p=room[p][2];
				printf("You moved East\n");

			}
			else if (direction[p][3] == 'e') {
				p=room[p][3];
				printf("You moved East\n");

			}
			else {
			printf("You can't go EAST!\n"); //Prints this if east is not an exit
			}

		}

		else if (userInput == 'w'){ //Allows the player to move west
			if (direction[p][0] == 'w') {
				p=room[p][0];
				printf("You moved West\n");

			}
			else if (direction[p][1] == 'w') {
				p=room[p][1];
				printf("You moved West\n");

			}
			else if (direction[p][2] =='w') {
				p=room[p][2];
				printf("You moved West\n");

			}
			else if (direction[p][3] == 'w') {
				p=room[p][3];
				printf("You moved West\n");

			}
			else {
				printf("You can't go WEST!\n"); //Prints this if west is not an exit
			}

			}
		
			else if (userInput == 'q'){ //Allows the player to quit the game
				break;
			}
	
			else {
				printf("Invalid Input\n"); //Prints "Invalid Input" if the player attempts to input an unknown character
			}
	}

	//Have to delete the arrays	

	for(i=0; i < roomCount; i++) {
		delete[] roomTitle[i]; 
	}
		delete[] roomTitle;

	for(i=0; i < roomCount; i++) {
		delete[] roomDesc[i]; 
	}
		delete[] roomDesc;

	for(i=0; i < roomCount; i++) {
		delete[] roomDirec[i]; 
	}
		delete[] roomDirec;


//	delete[] rooms;
	return(0);
}
