// This is a little clicker game made as a way to learn c++ and raylib, this is not meant to be a example at all, this is very messy code.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma clang diagnostic pop
#include "raylib-cpp.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>
#include <cmath>

// game variables
int clickCount = 0;
int CpC = 1;
int Mult = 1;

// upgrade costs & counts
int upg1C = 50;
int upg1A = 0;
int upg2C = 225;
int upg2A = 0;

void click() {
    clickCount += CpC * Mult;
}

void upgrade(int upgN) {
    if (upgN == 1) {
        if (clickCount >= upg1C) {
            clickCount -= upg1C;
            upg1A++;
            upg1C = (int)(50 * pow(1.15, upg1A));
            CpC++;
        } else {
            std::cout << "Not enough money! You need " << (upg1C - clickCount) << " more!" << std::endl;
        }
    }
    else if (upgN == 2) {
        if (clickCount >= upg2C) {
            upg2A++;
            clickCount -= upg2C;
            upg2C = (int)(225 * pow(1.15, upg2A));
            Mult++;
        } else {
            std::cout << "Not enough money! You need " << (upg2C - clickCount) << " more!" << std::endl;
        }
    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 800;

    raylib::Window window(screenWidth, screenHeight, "game");
    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        // recalculate every frame so layout updates as user resizes
        int w = GetScreenWidth();
        int h = GetScreenHeight();
        float s = w / 800.0f; // scale relative to base 800px width

        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RAYWHITE));
        GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(17 * s));
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);

        BeginDrawing();
        window.ClearBackground(GRAY);
        DrawLine(220 * s, 0, 220 * s, h, BLACK);

        if (GuiButton({350*s, 90*s, 200*s, 100*s}, "Click me!"))
            click();
        if (GuiButton({6*s, 50*s, 200*s, 100*s}, TextFormat("Upgrade 1: +1 Clicks\n\nCost: %d clicks", upg1C)))
            upgrade(1);
        if (GuiButton({6*s, 150*s, 200*s, 100*s}, TextFormat("Upgrade 2: +1 Multi\n\nCost: %d clicks", upg2C)))
            upgrade(2);

        DrawText(TextFormat("Clicks: %d", clickCount), (int)(400*s), (int)(60*s), (int)(24*s), RAYWHITE);
        DrawText("made by indpon", (w / 2) - (MeasureText("made by indpon", (int)(10*s)) / 2), (int)(10*s), (int)(10*s), RAYWHITE);
        EndDrawing();
    }
    return 0;
}
