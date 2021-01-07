#pragma once

#include <Windows.h>

#include "screen.h"

#define DIRECTION
#define COLLISION

typedef struct Snake {
	PCOORD coord;
	BOOL is_head;
	struct Snake *next;
} Snake;

typedef Snake *SNAKE;

SNAKE snake_add_tail(SNAKE head);

void snake_dealloc(SNAKE snake);

void snake_dealloc_all(SNAKE snake);

BOOL COLLISION snake_draw(SCREEN_BUFFER screen, SNAKE snake, int direction);

SNAKE snake_init(void);

int DIRECTION snake_move(SCREEN_BUFFER screen, SNAKE snake, int last_direction);
