#include "raylib.h"
#include <stdlib.h> // For rand() and srand()
#include <cstring>
#include <time.h>   // For time() to seed random number generator

#define GRID_SIZE 3
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE (SCREEN_WIDTH / GRID_SIZE)

typedef enum { EMPTY = 0, PLAYER_X, PLAYER_O } Cell;

void DrawGrid(Cell grid[GRID_SIZE][GRID_SIZE]);
int CheckWinner(Cell grid[GRID_SIZE][GRID_SIZE]);
bool IsBoardFull(Cell grid[GRID_SIZE][GRID_SIZE]);
void AITurn(Cell grid[GRID_SIZE][GRID_SIZE]);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic-Tac-Toe");
    SetTargetFPS(60);

    // Seed the random number generator
    srand(time(NULL));

    Cell grid[GRID_SIZE][GRID_SIZE] = { EMPTY };
    bool gameOver = false;
    bool draw = false;
    Cell currentPlayer = PLAYER_X; // Player starts first

    while (!WindowShouldClose()) {
        if (!gameOver) {
            if (currentPlayer == PLAYER_X && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (grid[row][col] == EMPTY) {
                    grid[row][col] = currentPlayer;
                    currentPlayer = PLAYER_O;

                    int winner = CheckWinner(grid);
                    if (winner != EMPTY) {
                        gameOver = true;
                    } else if (IsBoardFull(grid)) {
                        draw = true;
                        gameOver = true;
                    }
                }
            } else if (currentPlayer == PLAYER_O) {
                AITurn(grid);
                currentPlayer = PLAYER_X;

                int winner = CheckWinner(grid);
                if (winner != EMPTY) {
                    gameOver = true;
                } else if (IsBoardFull(grid)) {
                    draw = true;
                    gameOver = true;
                }
            }
        }

        if (gameOver && IsKeyPressed(KEY_R)) {
            memset(grid, 0, sizeof(grid));
            currentPlayer = PLAYER_X; // Player starts first
            gameOver = false;
            draw = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGrid(grid);

        if (gameOver) {
            if (draw) {
                DrawText("It's a Draw!", SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 20, 40, BLACK);
            } else {
                const char *message = (CheckWinner(grid) == PLAYER_X) ? "Player X Wins!" : "Player O Wins!";
                DrawText(message, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 20, 40, BLACK);
            }
            DrawText("Press R to Restart", SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 40, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawGrid(Cell grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);

            if (grid[i][j] == PLAYER_X) {
                DrawLine(x + 20, y + 20, x + CELL_SIZE - 20, y + CELL_SIZE - 20, RED);
                DrawLine(x + CELL_SIZE - 20, y + 20, x + 20, y + CELL_SIZE - 20, RED);
            } else if (grid[i][j] == PLAYER_O) {
                DrawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, CELL_SIZE / 2 - 20, BLUE);
            }
        }
    }
}

int CheckWinner(Cell grid[GRID_SIZE][GRID_SIZE]) {
    // Check rows and columns
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid[i][0] != EMPTY && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return grid[i][0];
        }
        if (grid[0][i] != EMPTY && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            return grid[0][i];
        }
    }

    // Check diagonals
    if (grid[0][0] != EMPTY && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        return grid[0][0];
    }
    if (grid[0][2] != EMPTY && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        return grid[0][2];
    }

    return EMPTY;
}

bool IsBoardFull(Cell grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

void AITurn(Cell grid[GRID_SIZE][GRID_SIZE]) {
    // Find all empty cells
    int emptyCells[GRID_SIZE * GRID_SIZE][2];
    int emptyCount = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == EMPTY) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    // Choose a random empty cell
    if (emptyCount > 0) {
        int choice = rand() % emptyCount;
        int row = emptyCells[choice][0];
        int col = emptyCells[choice][1];
        grid[row][col] = PLAYER_O;
    }
}
