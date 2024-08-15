#include "raylib.h"
#include <stdlib.h> 
#include <cassert>
#include <cstring>
#include <time.h>   

#define GRID_SIZE 3
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE (SCREEN_WIDTH / GRID_SIZE)

enum Cell{
    NONE,
    PLAYER,
    BOT
};

void render_image(char *file_path) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "annoying-viewer");

    Texture2D texture = LoadTexture(file_path);

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texture, (SCREEN_WIDTH - texture.width) / 2, (SCREEN_HEIGHT - texture.height) / 2, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}

void drawGrid(Cell grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);

            if (grid[i][j] == PLAYER) {
                // DrawLine(x + 20, y + 20, x + CELL_SIZE - 20, y + CELL_SIZE - 20, RED);
                // DrawLine(x + CELL_SIZE - 20, y + 20, x + 20, y + CELL_SIZE - 20, RED);
                DrawLineEx((Vector2){ static_cast<float>(x + 20), static_cast<float>(y + 20) }, (Vector2){ static_cast<float>(x + CELL_SIZE - 20), static_cast<float>(y + CELL_SIZE - 20) }, 10, RED);
                DrawLineEx((Vector2){ static_cast<float>(x + CELL_SIZE - 20), static_cast<float>(y + 20) }, (Vector2){ static_cast<float>(x + 20), static_cast<float>(y + CELL_SIZE - 20) }, 10, RED);
            } else if (grid[i][j] == BOT) {
                DrawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, CELL_SIZE / 2 - 20, BLUE);
                DrawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, (CELL_SIZE / 2) - 40, RAYWHITE);
            }
        }
    }
}

void botTurn(Cell grid[GRID_SIZE][GRID_SIZE]) {
    int emptyCells[GRID_SIZE * GRID_SIZE][2];
    int emptyCount = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == NONE) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int choice = rand() % emptyCount;
        int row = emptyCells[choice][0];
        int col = emptyCells[choice][1];
        grid[row][col] = BOT;
    }
}

bool isBoardFull(Cell grid[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if(grid[i][j] == NONE) {
                return false;
            }
        }
    }
    return true;
}
Cell checkWinner(Cell grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid[i][0] != NONE && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return grid[i][0];
        }
        if (grid[0][i] != NONE && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            return grid[0][i];
        }
    }

    if (grid[0][0] != NONE && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        return grid[0][0];
    }
    if (grid[0][2] != NONE && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        return grid[0][2];
    }

    return NONE;
}

Cell ttt() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "annoying-viewer");

    Color BACKGROUND_COLOR= { 30, 30, 46, 255 };

    SetTargetFPS(60);

    Cell grid[GRID_SIZE][GRID_SIZE] = { NONE };
    bool gameOver = false;
    bool draw = false;
    Cell currentPlayer = PLAYER; 
    Cell winner = NONE;

    while(!WindowShouldClose()) {
        if(!gameOver) {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                int col = mousePos.x / CELL_SIZE;
                int row = mousePos.y / CELL_SIZE;

                if(grid[row][col] == NONE) {
                    grid[row][col] = PLAYER;
                    currentPlayer = BOT;

                    winner = checkWinner(grid);
                    if(winner != NONE) {
                        gameOver = true;
                    } else if (isBoardFull(grid)) {
                        gameOver = true;
                        draw = true;
                    }
                }
            } else if (currentPlayer == BOT) {
                botTurn(grid);
                currentPlayer = PLAYER;

                winner = checkWinner(grid);
                if(winner != NONE) {
                    gameOver = true;
                } else if (isBoardFull(grid)) {
                    gameOver = true;
                    draw = true;
                }
            }
        }

        if(gameOver && IsKeyPressed(KEY_C)) {
            CloseWindow();
            if(winner == PLAYER) return PLAYER;
            else if(winner == BOT) return BOT;
            else  return NONE;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (gameOver) {
            if (draw) {
                DrawText("It's a Draw!", SCREEN_WIDTH / 4 + 20, SCREEN_HEIGHT / 2 - 20, 40, BLACK);
            } else {
                winner = checkWinner(grid);
                if(winner == PLAYER) {
                    const char *message = "You Win, CHEATER!";
                    DrawText(message, SCREEN_WIDTH / 4 - 40, SCREEN_HEIGHT / 2 - 20, 40, BLACK);
                }else {
                    const char *message = "I Win, fair play!";
                    DrawText(message, SCREEN_WIDTH / 4 , SCREEN_HEIGHT / 2 - 20, 40, BLACK);
                }

            }
            DrawText("Press 'C' to Continue", SCREEN_WIDTH / 4 + 30, SCREEN_HEIGHT / 2 + 40, 20, GRAY);
        } else drawGrid(grid);
        EndDrawing();
    }
    CloseWindow();
    return NONE;
}

bool play_again() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "wanna play again");
    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        if(IsKeyPressed(KEY_T)) {
            CloseWindow();
            return true;
        }else if(IsKeyPressed(KEY_Q)) {
            CloseWindow();
            return false;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Try again or be a chicken", SCREEN_WIDTH/2-150, SCREEN_HEIGHT/2 - 60, 20, LIGHTGRAY);
            DrawText("To try again press 'T'", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2 - 30, 20, LIGHTGRAY);
            DrawText("Be a chicken press 'Q'", SCREEN_WIDTH/2-130, SCREEN_HEIGHT/2 , 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return false;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    bool play = true;
    
    while(play) {
        Cell winner = ttt();
        if(winner == PLAYER || winner == NONE) {
            assert(argc == 2 && "file not provided");
            char *file_path = argv[1];
            play = false;
            render_image(file_path);
        }else {
            play = play_again();
        }
    }

    return 0;
}

