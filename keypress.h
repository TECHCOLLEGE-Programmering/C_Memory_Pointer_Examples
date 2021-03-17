#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* 
All rights: micheal.dipperstein.com
Source: http://michael.dipperstein.com/keypress.html

simply wait for a key to be pressed 
	printf("press a key to continue\n");
	keypress(0);

wait for the space bar 
	printf("hit the spacebar to continue\n");
	while (keypress(0) != ' ');
*/

/* 
sleep until a key is pressed and return value. echo = 0 disables key echo. 
*/
int keypress(unsigned char echo)
{
    struct termios savedState, newState;
    int c;

    if (-1 == tcgetattr(STDIN_FILENO, &savedState))
    {
        return EOF;     /* error on tcgetattr */
    }

    newState = savedState;

    if ((echo = !echo)) /* yes i'm doing an assignment in an if clause */
    {
        echo = ECHO;    /* echo bit to disable echo */
    }

    /* disable canonical input and disable echo.  set minimal input to 1. */
    newState.c_lflag &= ~(echo | ICANON);
    newState.c_cc[VMIN] = 1;

    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState))
    {
        return EOF;     /* error on tcsetattr */
    }

    c = getchar();      /* block (withot spinning) until we get a keypress */

    /* restore the saved state */
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState))
    {
        return EOF;     /* error on tcsetattr */
    }

    return c;
}