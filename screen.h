#pragma once

#include <Windows.h>

typedef struct ScreenBuffer {
	wchar_t* buf;
	UINT screen_width;
	UINT screen_height;
} ScreenBuffer;

typedef ScreenBuffer* SCREEN_BUFFER;

void screen_buffer_dealloc(SCREEN_BUFFER screen);

_Notnull_ SCREEN_BUFFER  screen_buffer_init(const UINT screen_width, const UINT screen_height);

void screen_buffer_reset(SCREEN_BUFFER screen);

BOOL screen_buffer_write(SCREEN_BUFFER screen, wchar_t value, const UINT x, const UINT y);