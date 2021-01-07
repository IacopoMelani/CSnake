#include "snake.h"

#include <string.h>

static void snake_move_childs(SNAKE node, SNAKE parent);
static BOOL snake_same_coord(SNAKE s1, SNAKE s2);

SNAKE snake_add_tail(SNAKE head)
{
	SNAKE new_head;

	new_head = snake_init();

	head->is_head = FALSE;
	new_head->is_head = TRUE;

	new_head->coord->X = head->coord->X;
	new_head->coord->Y = head->coord->Y;

	new_head->next = head;

	return new_head;
}

void snake_dealloc(SNAKE snake)
{
	free(snake->coord);
	snake->coord = NULL;

	free(snake);
	snake = NULL;
}

void snake_dealloc_all(SNAKE snake)
{
	SNAKE pivot, new_head;

	pivot = snake;
	new_head = pivot;

	while (pivot != NULL)
	{
		new_head = pivot->next;

		snake_dealloc(pivot);

		pivot = new_head;
	}
}

BOOL snake_draw(SCREEN_BUFFER screen, SNAKE snake, int direction)
{
	SNAKE pivot;
	BOOL collision = FALSE;

	pivot = snake;

	while (pivot != NULL)
	{
		if (pivot->is_head) 
		{
			switch (direction)
			{
			case VK_UP:
				screen_buffer_write(screen, '^', pivot->coord->X, pivot->coord->Y);
				break;
			case VK_DOWN:
				screen_buffer_write(screen, 'V', pivot->coord->X, pivot->coord->Y);
				break;
			case VK_LEFT:
				screen_buffer_write(screen, '<', pivot->coord->X, pivot->coord->Y);
				break;
			case VK_RIGHT:
			default:
				screen_buffer_write(screen, '>', pivot->coord->X, pivot->coord->Y);
				break;
			}
		}
		else
		{
			if (snake_same_coord(snake, pivot) && snake->next != pivot) 
			{
				screen_buffer_write(screen, 'X', pivot->coord->X, pivot->coord->Y);
				collision = TRUE;
			}
			else
			{
				screen_buffer_write(screen, 'O', pivot->coord->X, pivot->coord->Y);
			}
		}
		pivot = pivot->next;
	}

	return collision;
}

SNAKE snake_init(void)
{
	PCOORD coord = malloc(sizeof(COORD));
	if (coord == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(coord, 0, sizeof(PCOORD));

	SNAKE snake = malloc(sizeof(Snake));
	if (snake == NULL)
	{
		exit(EXIT_FAILURE);
	}
	memset(snake, 0, sizeof(Snake));

	snake->coord = coord;
	snake->is_head = TRUE;
	snake->next = NULL;

	return snake;
}

int snake_move(SCREEN_BUFFER screen, SNAKE snake, int last_direction)
{
	snake_move_childs(snake->next, snake);

	if (GetAsyncKeyState(VK_UP) && last_direction != VK_DOWN)
	{
		snake->coord->Y -= 1;
		last_direction = VK_UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && last_direction != VK_UP)
	{
		snake->coord->Y += 1;
		last_direction = VK_DOWN;
	}
	else if (GetAsyncKeyState(VK_LEFT) && last_direction != VK_RIGHT)
	{
		snake->coord->X -= 1;
		last_direction = VK_LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && last_direction != VK_LEFT)
	{
		snake->coord->X += 1;
		last_direction = VK_RIGHT;
	}
	else {

		switch (last_direction)
		{
		case VK_UP:
			snake->coord->Y -= 1;
			break;
		case VK_DOWN:
			snake->coord->Y += 1;
			break;
		case VK_LEFT:
			snake->coord->X -= 1;
			break;
		case VK_RIGHT:
		default:
			snake->coord->X += 1;
			break;
		}
	}

	if (snake->coord->X > screen->screen_width) { snake->coord->X = 0; }
	if (snake->coord->X < 0) { snake->coord->X = screen->screen_width; }
	if (snake->coord->Y < 0) { snake->coord->Y = screen->screen_height; }
	if (snake->coord->Y > screen->screen_height) { snake->coord->Y = 0; }

	return last_direction;
}

static void snake_move_childs(SNAKE node, SNAKE parent)
{
	if(node == NULL)
	{
		return;
	}

	if (node->next != NULL)
	{
		snake_move_childs(node->next, node);
	}

	if (!snake_same_coord(parent, node))
	{
		node->coord->X = parent->coord->X;
		node->coord->Y = parent->coord->Y;
	}
}

static BOOL snake_same_coord(SNAKE s1, SNAKE s2)
{
	return s1->coord->X == s2->coord->X && s1->coord->Y == s2->coord->Y;
}