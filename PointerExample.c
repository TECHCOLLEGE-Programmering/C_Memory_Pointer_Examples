#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>
#include "keypress.h"

/*
 * Author: lkri-dev 
 * Source: https://github.com/lkri-dev/Memory-PointerExample.git

 * Compiler notes
 * gcc -o a PointerExample.c -lncurses -lm
 * ./a

 * Helpfull links:
 *	curses.h:			https://courses.cs.washington.edu/courses/cse451/99wi/Section/gccintro.html
 *	How to C in 2016:	https://matt.sh/howto-c
 */

//Defines
#define NAMEOF(name) #name

//Global varialbles
int menuControl = 0; //controls highlight in menu
bool loopControl = true; //Controls while loop of program
int keyHit = 0;

int color = 34; //sets color of highlighted text. 31 = red ; 32 = green ; 33 = yellow ; 34 = blue ; 35 = Magenta ; 36 = cyan.

char *menuOptions[] = { //contains the menu options
	"Datatype Describtion",
	"Array Describtion",
	"Pointer Example",
	"binary",
	"Bit shitft eksempel",
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
 * DatatypeDescribtion 
 * The first example
 * Variables have addresses in memory and different sizes
 * Prints variable name, size, number of possible values, and a diagram with a box for each byte including the start and end addresses. 
*/
void DatatypeDescribtion () {
	short var1;
	const int var1Address = (int)&var1;
	const short var1Size = sizeof(var1);
	const int numberOfBits = (var1Size * 8); //8 is the number of bits in a byte
	const unsigned long long possibleValues = pow(2 ,numberOfBits); //2^n, 2 comes from the posible stage of a bit 1 and 0.


	printf("Variables have adresses in memory\n\n");	

	printf("Size of %s variable: %d bytes\n", NAMEOF(var1), var1Size );
	//printf("Size in bits: %d\n", numberOfBits);
	printf("Number of possible values of %s is %lld\n", NAMEOF(var1), possibleValues);
	printf("Address of %s variable: \n0x%X\n", NAMEOF(var1), var1Address);
	PrintMemoryDiagram(var1Size);
	printf("0x%X\n", var1Address + var1Size);
	printf("\n");
	keypress(0);
}
/*
 * Array datatype describtion 
 * The seacond example
 * Does the same as DataTypeDescribtion except for arrays.
*/
void ArrayExample () {
	char arraySize = 6;
	char CharArray[arraySize];
	const int var2Address = &CharArray;
	const short var2Size = sizeof(CharArray);

	printf("Variable %s of type char[%d])\n\n", NAMEOF(CharArray), arraySize);

	printf("Size of of %s variable: %d bytes\n", NAMEOF(CharArray), var2Size );

	printf("Address of %s: \n0x%X\n", NAMEOF(CharArray), (int)&CharArray );

	for (int i = 0; i >= arraySize; i++) {
		printf("0x%X\n", (int)&CharArray[i]);

	}
	PrintMemoryDiagram(var2Size);
	printf("0x%X\n", var2Address + var2Size);
	printf("\n");
}

/*
 * PointerExample 
 * The third pointer example
 * What is pointers?
*/
void PointerExample () {
	/* Pointer of integer type, this can hold the
    * address of a integer type variable.
    */
	int *p;

	int var = 10;


	/* Assigning the address of variable var to the pointer p.
	* The p can hold the address of var because var is an 
	* integer type variable.
	*/
	p = &var;

	printf("Here we can see de different addresses of var and p, and that p is pointing to the address of var.\n\n");

	printf("Value of variable var is: %d \n", var);
	printf("Value of derefferancing of the pointer p (*p) is: %d \n", *p); //*derefferancing of address
	printf("Address of variable var (&var) is: %p \n", &var); //& adresse of variable
	printf("Address of of what p is pointing to is: %p \n", p);
	printf("Address of pointer p (&p) is: %p \n", &p);
}

/*
 * Example for bit operations.
 */
int shift () {
	int a = 0;
	printf("Before any shift %d\n", a);
	a |= (1 << 6); //Set a bit
	//printf("%u ",num&maxPow ? 1 : 0);
	printf("After a |= (1 << 6); //Set a bit %d\n", a);
	a &= ~(1 << 6); //clear a bit
	printf("After a &= ~(1 << 6); //clear a bit %d\n", a);
    a ^= (1 << 4); //toggle bit
	printf("After a ^= (1 << 4); //toggle bit %d\n", a);
	a <<= 2; //left shift whold byte[]
	printf("After a <<= 2; //left shift whole byte[] %d\n", a);
	a >>= 2; //right shift whold byte[]
	printf("After a >>= 2; //right shift whole byte[] %d\n", a);
	return a;
}

int IfTrue (){
	printf("Here is an example of binary values used as true and false, as long as a value is above 0 it is true.");
	if (0b10000000){
		printf("0b10000000 - Just one 1 is enough to be true\n");
	}
	if(0b11111111){
		printf("0b11111111 - all 1s is also true\n");
	}
	if(0b00000000){
		printf("0b00000000 - all 0s is false\n");
	}
}

/*
 * MenuControl 
 * Calls PrintMenu and then controls the program flow based on menuControl.
 */
void MenuControl (void) {
	switch (menuControl) {
		case 0:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			DatatypeDescribtion ();
			break;
		
		case 1:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			ArrayExample ();
			break;
			
		case 2:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			PointerExample();
			break;
			
		case 3:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			IfTrue();
			break;
			
		case 4:
			printf("Menu Option: %s\n", menuOptions[menuControl]);
			shift();
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
	printf("_________________________________");
	printf("\n");
}

/*
 * Main
 * Contain a switch case that controls menu based on keypress input.
 */
int main(void) {
	printf("Press 'w' and 's' or arrow up and down to navigate the menu.\n");
	printf("Press 'e' to exit.\n");
	printf("Press enter to select the red option.\n\n");
	printf("Press any key to continue.\n");
	keypress(0);
	menuControl = 0;
	PrintMenu();
		
	while (loopControl) {
		printf("\033[0m");
		
		keyHit = keypress(0);
 
		if (keyHit != 0)
		{
			switch(keyHit){
				case 65:
				case 119: //119(w) or 65(arrow key up)
					--menuControl;
					PrintMenu();
					break;
				
				case 66:
				case 115: //115(s) or 66(arrow key down)
					++menuControl;
					PrintMenu();
					break;
				
				case 10: //10(enter)
					MenuControl();
					break;
					
				case 101: //101(e)
					printf("exit\n");
					loopControl = false;
					break;
			}
		}
	}
}

