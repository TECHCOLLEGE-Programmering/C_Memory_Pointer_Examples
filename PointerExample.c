#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>
#include "keypress.h"

/*
Author: lkri-dev 
Source: https://github.com/lkri-dev/ANSICMenu

Compiler notes
gcc -o menu Menu.c -lncurses
./menu

Helpfull links:
	curses.h:
	https://courses.cs.washington.edu/courses/cse451/99wi/Section/gccintro.html

	https://matt.sh/howto-c
*/

//Defines
#define NAMEOF(name) #name

//Global varialbles
int menuControl = 0; //controls highlight in menu
bool loopControl = true; //Controls while loop of program
int hit = 0;

int color = 34; //sets color of highlighted text. 31 = red ; 32 = green ; 33 = yellow ; 34 = blue ; 35 = Magenta ; 36 = cyan.

char *menuOptions[] = { //contains the menu options
	"Pointer Example 1",
	"Pointer Example 2",
	"Pointer Example 3",
	"Pointer Example 4",
	"Exit",
};
int const n_options = sizeof(menuOptions) / sizeof(char *); // contain size of menu options

/*
 * PrintMemoryDiagram
*/
void PrintMemoryDiagram (short size) {
	printf("+--------------------+\n");
	for (int i = 0; i+1 <= size; i++) {
		printf("|      1 byte        |\n");
		printf("+--------------------+\n");
	}
}

/*
 * PointerExample1 
 * The first pointer example
*/
void Char () {
	short arraySize = 10;
	char var2[arraySize];
	const int var2Address = &var2;
	const short var2Size = sizeof(var2);
	
	printf("Variable %s of type char[%d])\n\n", NAMEOF(var2), arraySize);
	
	printf("Size of of %s variable: %d bytes\n", NAMEOF(var2), var2Size );
	
	printf("Address of %s variable: \n0x%X\n", NAMEOF(var2), &var2 );
	PrintMemoryDiagram(var2Size);
	printf("0x%X\n", var2Address + var2Size);
	printf("\n");
}

/*
 * PointerExample1 
 * The first pointer example
 * Variables have adresses in memory and different sizes
*/
void PointerExample1 () {
	long var1;
	const int var1Address = &var1;
	const short var1Size = sizeof(var1);
	const int numberOfBits = (var1Size * 8); //8 is the number of bits in a byte
	const unsigned long long possibleValues = pow(2 ,numberOfBits); //2^n, 2 comes from the posible stage of a bit 1 and 0.
	
	printf("%d\n", numberOfBits);
	printf("Variables have adresses in memory\n\n");
	
	printf("Variables %s(int))\n\n", NAMEOF(var1));
	
	
	printf("Size of %s variable: %d bytes\n", NAMEOF(var1), var1Size );
	printf("Number of possible values of %s is %ld\n", NAMEOF(var1), possibleValues);
	printf("Address of %s variable: \n0x%X\n", NAMEOF(var1), &var1 );
	PrintMemoryDiagram(var1Size);
	printf("0x%X\n", var1Address + var1Size);
	printf("\n");
}
/*
 * PointerExample2 
 * The second pointer example
 * What is pointers?
*/
void PointerExample2 () {
	printf("\n");
	int    *ip;    /* pointer to an integer */
	double *dp;    /* pointer to a double */
	float  *fp;    /* pointer to a float */
	char   *chp;     /* pointer to a character */
}

/*
 * MenuControl 
 * Calls PrintMenu and then controls the program flow based on menuControl.
*/
void MenuControl (void) {
	switch (menuControl) {
		case 0:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			PointerExample1 ();
			break;
		
		case 1:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			PointerExample2 ();
			break;
		
		case 2:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			Char ();
			break;
			
		case 3:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			
			break;
			
		case sizeof(menuOptions) / sizeof(char *) - 1: // "Exit"
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			loopControl = false;
			break;
	}
}

/*
 * PrintMenu 
 * Prints out menuOptions and hightlights based on menuControl.
*/
void PrintMenu (void) {
	system("clear");
	
	if (menuControl < 0) {
		menuControl = 0;
	}
	else if (menuControl > n_options-1) {
		menuControl = n_options-1;
	}
	
	for (int i = 0; i < n_options; ++i) {
		if (menuControl == i) {
			printf("\033[1;%dm", color);
			printf("%s\n", menuOptions[i]);
			
		} else {
			printf("\033[0m");
			printf("%s\n", menuOptions[i]);
		}
	}
}

/*
 * Main
 * Contain a switch case that controls menu based on keypress input.
*/
int main(void) {
	
	//while (!kbhit()){
	//	printf("You haven't pressed a key.\n");
	//}
      
	
	printf("Press 'w' and 's' or arrow up and down to navigate the menu.\n");
	printf("Press 'e' to exit.\n");
	printf("Press enter to select the red option.\n\n");
	printf("Press any key to continue.\n");
	keypress(0);
	menuControl = 0;
	PrintMenu();
		
	while (loopControl) {
		printf("\033[0m");
		
		hit = keypress(0);
 
		if (hit != 0)
		{
			switch(hit){
				case 65:
				case 119: //w or 65(arrow key up)
					--menuControl;
					PrintMenu();
					break;
				
				case 66:
				case 115: //s or 66(arrow key down)
					++menuControl;
					PrintMenu();
					break;
				
				case 10:
					MenuControl();
					break;
					
				case 101: //e
					printf("exit\n");
					loopControl = false;
					break;
			}
		}
	}
}

