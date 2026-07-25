#include <stdio.h> // std I/O functions
#include <stdbool.h> // boolean (True or False)
#include <string.h> // string manipulation functions
#include <SDL2/SDL.h> // SDL2 graphics library

// size of each square cell in the maze (pixels), you can match it to how big you like
#define CELL_SIZE 30
// window dimensions
#define WINDOW_WIDTH 300 
#define WINDOW_HEIGHT 300
// number of rows and cols in the grid
#define ROWS WINDOW_WIDTH / CELL_SIZE
#define COLS WINDOW_HEIGHT / CELL_SIZE

// represents one square (cell) in the maze
// each cell knows its neighbouring cells and stores information used during recursive pathfinding.
typedef struct cell
{
    // unique identifier (e.g. "34")
    char id[3];
    // pointers to neighbouring cells
    struct cell *north;
    struct cell *south;
    struct cell *east;
    struct cell *west;
    // true = wall; false = walkable path
    bool wall;
    // prevents recursion from revisiting the same cell
    bool visited;
    // marks cells belonging to the successful path
    bool on_path;
} Cell;

// creates every cell in the maze
// for each cell:
// - receives an ID
// - stores pointers to its neighbouring cells
// - starts as a wall
// - is marked as unvisited
void initialize_cells(Cell cells[][COLS])
{
    // connects neighbouring cells using pointers
    // edge cells have NULL neighbours
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

// draws every visible maze cell onto the window.
// yellow = walkable path
// red = final solution path
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
                // draws the solution path in red,
                // otherwise, draw ordinary walkable cells in yellow
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

// left mouse click toggles a cell between wall, walkable path,
// then clicking again restores the wall
void toggle_wall(int mouse_x, int mouse_y, Cell cells[][COLS])
{
    int row = mouse_x / CELL_SIZE;
    int col = mouse_y / CELL_SIZE;

    cells[row][col].wall = !cells[row][col].wall;
    cells[row][col].visited = false;
}

// recursive depth-first search (DFS)
// starting from one cell, recursively explores neighbouring cells until a path reaches the opposite side of the maze
// successful cells are marked as part of the final solution path
void find_path(int x, int y, Cell cells[][COLS], bool *trackFound)
{
    // stops recursion if this cell has already been visited
	if (cells[x][y].visited)
	{
		return;
	}
	cells[x][y].visited = true;
    // ignores positions outside the maze or cells that are walls
	if (x < 0 || y < 0 || x >= ROWS || y >= COLS || cells[x][y].wall)
	{
		return;
	}
    // goal reached
    // the search has arrived at the opposite side
	if (x == COLS - 1)
	{
		*trackFound = true;
		cells[x][y].on_path = true; 
		return;
	}
    // explore neighbouring cells
    // 1. right (x + 1)
	find_path(x + 1, y, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
    // 2. down (y + 1)
	find_path(x, y + 1, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
    // 3. left (x - 1)
	find_path(x - 1, y, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
	// 4. up (y - 1)
	find_path(x, y - 1, cells, trackFound);
	if (*trackFound)
	{
		cells[x][y].on_path = true; 
		return;
	}
}

//  program entry point
/*  creates SDL window
    handles user interaction
    continuously redraws the maze
    and starts recursive searches*/
int main(int argc, char *args[])
{
    // initializes SDL subsystem
    SDL_Init(SDL_INIT_EVERYTHING);

    // creates application window
    SDL_Window *window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, 0);
    // renderer is responsible for drawing graphics
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    Cell cells[ROWS][COLS];
    initialize_cells(cells);

    bool isRunning = true;
    SDL_Event event;

    bool pathFound = false;
    
    // main application loop - continues running until window closes
    while (isRunning)
    {
        if (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            // handle mouse clicks
            case SDL_MOUSEBUTTONDOWN:
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                // left click: toggles wall into a walkable path
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    toggle_wall(mouse_x, mouse_y, cells);
                }
                // right click starts recursive DFS only if
                // the selected cell is on the left edge and is a valid path
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
        // clear previous frame
        SDL_RenderClear(renderer);
        // draw the updated maze
        draw_cells(renderer, cells);
        SDL_RenderPresent(renderer);
    }
    // release SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 


