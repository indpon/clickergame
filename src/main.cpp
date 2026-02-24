// This is a little clicker game made as a way to learn c++ and raylib, this is not meant to be a example at all, this is very messy code.

#include "raylib-cpp.hpp"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>
#include <cmath>

// game variables
int clickCount = 0;
int baseClickAmount = 1;
int Mult = 1;

float achievementTimer = 0.0f;

// upgrade costs & counts
int upg1Cost = 50;
int upg1Amount = 0;
int upg2Cost = 225;
int upg2Amount = 0;

// achivements

bool ach1Earned = false;

void click() {
    clickCount += baseClickAmount * Mult;
}

void upgrade(int upgN) {
    if (upgN == 1) {
        if (clickCount >= upg1Cost) {
            clickCount -= upg1Cost;
            upg1Amount++;
            upg1Cost = (int)(50 * pow(1.15, upg1Amount));
            baseClickAmount++;
        } else {
            std::cout << "Not enough money! You need " << (upg1Cost - clickCount) << " more clicks!" << std::endl;
        }
    }
    else if (upgN == 2) {
        if (clickCount >= upg2Cost) {
            upg2Amount++;
            clickCount -= upg2Cost;
            upg2Cost = (int)(225 * pow(1.15, upg2Amount));
            Mult++;
        } else {
            std::cout << "Not enough money! You need " << (upg2Cost - clickCount) << " more clicks!" << std::endl;
        }
    }
}


int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 800;
    

    int FPS = 60;

    raylib::Window window(screenWidth, screenHeight, "game");
    
    SetWindowMinSize(800, 800); // make it so people cant cut off my precious buttons

    SetTargetFPS(FPS);

    while (!window.ShouldClose())
    {
        
        int w = GetScreenWidth();
        int h = GetScreenHeight();
        float s = w / 800.0f; // scale factor

        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RAYWHITE));
        GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(17 * s));
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);

        BeginDrawing();
        window.ClearBackground(GRAY);
        DrawLine(220 * s, 0, 220 * s, h, BLACK);

        achievementTimer -= GetFrameTime();


        if (clickCount >=10000 && !ach1Earned) {
            ach1Earned = true;
            achievementTimer = 2.0f;
            baseClickAmount += (baseClickAmount * 5) / 100;
        }

        if (achievementTimer > 0.0f) {
            DrawText("Achievement 1 unlocked! +5% clicks boost", 300*s, 700*s, 22*s, GREEN);
        }

        if (GuiButton({350*s, 90*s, 200*s, 100*s}, "Click me!"))
            click();
        if (GuiButton({6*s, 50*s, 200*s, 100*s}, TextFormat("Upgrade 1: +1 Clicks\n\nCost: %d clicks", upg1Cost)))
            upgrade(1);
        if (GuiButton({6*s, 150*s, 200*s, 100*s}, TextFormat("Upgrade 2: +1 Multi\n\nCost: %d clicks", upg2Cost)))
            upgrade(2);

        DrawText(TextFormat("Clicks: %d", clickCount), (int)(400*s), (int)(60*s), (int)(24*s), RAYWHITE);
        DrawText("made by indpon", (w / 2) - (MeasureText("made by indpon", (int)(10*s)) / 2), (int)(10*s), (int)(10*s), RAYWHITE);
        EndDrawing();
    }
    return 0;
}
