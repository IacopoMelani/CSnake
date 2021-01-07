#include "console.h"

HANDLE console_screen_buffer_generic_init(void)
{
	HANDLE hConsole;
	
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	return hConsole;
}