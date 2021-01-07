#include <Windows.h>
#include <time.h>
#include <stdio.h>

#include "console.h"
#include "screen.h"
#include "snake.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40

#define SCREEN_SIZEOF sizeof(wchar_t) * (SCREEN_WIDTH * SCREEN_HEIGHT)

int main()
{
	SCREEN_BUFFER screen = screen_buffer_init(SCREEN_WIDTH, SCREEN_HEIGHT);
		
	HANDLE hConsole = console_screen_buffer_generic_init();
	DWORD dwBytesWritten = 0;

	int last_direction = VK_RIGHT;

	SNAKE snake = snake_init();

	while (1)
	{
		screen_buffer_reset(screen);

		last_direction = snake_move(screen, snake, last_direction);
		if (snake_draw(screen, snake, last_direction))
		{
			break;
		}

		COORD c = { 0, 0 };
		WriteConsoleOutputCharacter(hConsole, screen->buf, SCREEN_WIDTH * SCREEN_HEIGHT, c, &dwBytesWritten);

		if (last_direction == VK_UP || last_direction == VK_DOWN)
		{
			Sleep(120);
		}
		else
		{
			Sleep(75);
		}

		snake = snake_add_tail(snake);
	}

	printf("\nHai perso!");

	snake_dealloc_all(snake);

	screen_buffer_dealloc(screen);

	return 0;
}