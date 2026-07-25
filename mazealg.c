#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#define CELL_SIZE 30
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300
#define ROWS WINDOW_WIDTH / CELL_SIZE
#define COLS WINDOW_HEIGHT / CELL_SIZE

typedef struct cell
{
    char id[3];
    struct cell *north;
    struct cell *south;
    struct cell *east;
    struct cell *west;
    bool wall;
    bool visited;
    bool on_path;
} Cell;

void initialize_cells(Cell cells[][COLS])
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            sprintf(cells[r][c].id, "%d%d", r, c);
            cells[r][c].north = (r > 0) ? &cells[r - 1][c] : NULL;
            cells[r][c].south = (r < ROWS - 1) ? &cells[r + 1][c] : NULL;
            cells[r][c].east = (c < COLS - 1) ? &cells[r][c + 1] : NULL;
            cells[r][c].west = (c > 0) ? &cells[r][c - 1] : NULL;

            cells[r][c].wall = true;
            cells[r][c].visited = false;
            cells[r][c].on_path = false;
        }
    }
}

void draw_cells(SDL_Renderer *renderer, Cell cells[][COLS])
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            SDL_Rect rect;
            rect.y = CELL_SIZE * c;
            rect.x = CELL_SIZE * r;
            rect.h = CELL_SIZE;
            rect.w = CELL_SIZE;

            if (!cells[r][c].wall)
            {
                if (cells[r][c].on_path)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                }
                
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void toggle_wall(int mouse_x, int mouse_y, Cell cells[][COLS])
{
    int row = mouse_x / CELL_SIZE;
    int col = mouse_y / CELL_SIZE;

    cells[row][col].wall = !cells[row][col].wall;
    cells[row][col].visited = false;
}

void find_path(int x, int y, Cell cells[][COLS], bool *trackFound)
{
	if (cells[x][y].visited)
	{
		return;
	}
	cells[x][y].visited = true;

	if (x < 0 || y < 0 || x >= ROWS || y >= COLS || cells[x][y].wall)
	{
		return;
	}

	if (x == COLS - 1)
	{
		*trackFound = true;
		cells[x][y].on_path = true; 
		return;
	}

	find_path(x + 1, y, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}

	find_path(x, y + 1, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}

	find_path(x - 1, y, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
	
	find_path(x, y - 1, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
}

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Cell cells[ROWS][COLS];
    initialize_cells(cells);

    bool isRunning = true;
    SDL_Event event;

    bool pathFound = false;

    while (isRunning)
    {
        if (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    toggle_wall(mouse_x, mouse_y, cells);
                }
                
                if (event.button.button == SDL_BUTTON_RIGHT)
				{
					int row = mouse_x / CELL_SIZE;
					int col = mouse_y / CELL_SIZE;
					if (!cells[row][col].wall && row == 0)
					{
						bool trackFound = false;
						find_path(row, col, cells, &trackFound);
					}
				}
				break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);

        draw_cells(renderer, cells);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 


