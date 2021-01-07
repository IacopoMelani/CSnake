#include "screen.h"

#include <malloc.h>
#include <string.h>

#define AT_COORD(X, Y) ((Y) * (SCREEN_WIDTH) + (X))

static unsigned int at_coord(const SCREEN_BUFFER screen, const UINT x, const UINT y);
	
void screen_buffer_dealloc(SCREEN_BUFFER screen)
{
	free(screen->buf);
	screen->buf = NULL;

	free(screen);
	screen = NULL;
}

_Notnull_ SCREEN_BUFFER screen_buffer_init(const UINT screen_width, const UINT screen_height)
{
#ifndef SCREEN_SIZEOF
#define BUFFER_SIZEOF sizeof(wchar_t) * (screen_width * screen_height)
#endif // !SCREEN_SIZEOF

	wchar_t* buf = malloc(BUFFER_SIZEOF);
	if (buf == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(buf, 0, BUFFER_SIZEOF);

	SCREEN_BUFFER screen = malloc(sizeof(ScreenBuffer));
	if (screen == NULL)
	{
		exit(EXIT_FAILURE);
	}

	screen->buf = buf;
	screen->screen_height = screen_height;
	screen->screen_width = screen_width;

	screen_buffer_reset(screen);

	return screen;
}

void screen_buffer_reset(SCREEN_BUFFER screen)
{
	for (int x = 0; x < screen->screen_width; x++)
	{
		for (int y = 0; y < screen->screen_height; y++)
		{
			screen->buf[at_coord(screen, x, y)] = '.';
		}
	}
}

BOOL screen_buffer_write(SCREEN_BUFFER screen, wchar_t value, const UINT x, const UINT y)
{
	if (x > screen->screen_width || y > screen->screen_height)
	{
		return FALSE;
	}

	screen->buf[at_coord(screen, x, y)] = value;

	return TRUE;
}

static unsigned int at_coord(const SCREEN_BUFFER screen, const UINT x, const UINT y)
{
	return y * screen->screen_width + x;
}
