#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40

#define SCREEN_SIZEOF sizeof(wchar_t) * (SCREEN_WIDTH * SCREEN_HEIGHT)

#define AT_COORD(X, Y) ((Y) * (SCREEN_WIDTH) + (X))

int main()
{
	wchar_t* screen = malloc(SCREEN_SIZEOF);
	if (screen == NULL)
	{
		return 1;
	}
	memset(screen, 0, SCREEN_SIZEOF);
		
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			screen[AT_COORD(x, y)] = ' ';
		}
	}

	int pos_x = 0;
	int pos_y = 0;

	time_t tp1;
	time(&tp1);

	time_t tp2;
	time(&tp2);

	int last_direction = VK_RIGHT;

	while (1)
	{
		screen[AT_COORD(pos_x, pos_y)] = ' ';
		if (GetAsyncKeyState(VK_UP))
		{
			pos_y -= 1;
			last_direction = VK_UP;
		} 
		else if (GetAsyncKeyState(VK_DOWN))
		{
			pos_y += 1;
			last_direction = VK_DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT)) 
		{
			pos_x -= 1;
			last_direction = VK_LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) 
		{
			pos_x += 1;
			last_direction = VK_RIGHT;
		}
		else {

			switch (last_direction)
			{
			case VK_UP:
				pos_y -= 1;
				break;
			case VK_DOWN:
				pos_y += 1;
				break;
			case VK_LEFT:
				pos_x -= 1;
				break;
			case VK_RIGHT:
			default:
				pos_x += 1;
				break;
			}
		}

		if (pos_x > SCREEN_WIDTH) { pos_x = 0; pos_y += 1; }
		if (pos_y > SCREEN_HEIGHT) { pos_y = 0; }

		screen[AT_COORD(pos_x, pos_y)] = '@';

		screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
		COORD c = { 0, 0 };
		WriteConsoleOutputCharacter(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, c, &dwBytesWritten);

		Sleep(75);
	}

	return 0;
}