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
int clickCount = 99999;
int CpC = 1;
int Mult = 1;

// upgrade costs & counts
int upg1C = 50; // cost
int upg1A = 0; // amount

int upg2C = 225;
int upg2A = 0;

void click() {
    clickCount += CpC * Mult;
}

void upgrade(int upgN) {
    // do different things based off of the upgrade number it gets passed
    
    if (upgN == 1) { // TODO: Make a better version of this upgrade thing, this is stupid.
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
        if (clickCount >=upg2C) {
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

    

    int screenWidth = 800; // x
    int screenHeight = 800; // y
    


    raylib::Window window(screenWidth, screenHeight, "game");
    SetTargetFPS(60);

    
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RAYWHITE));
    GuiSetStyle(DEFAULT, TEXT_SIZE, 17);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);



    while (!window.ShouldClose())
    {

        BeginDrawing();
        window.ClearBackground(GRAY);

        DrawLine(220, 0, 220, 800, BLACK); // align wit the upgrades, leaving a little space

        
        if (GuiButton({350, 90, 200, 100}, "Click me!")) // main button
            click();

        if (GuiButton({6, 50, 200, 100}, TextFormat("Upgrade 1: +1 Clicks\n\nCost: %d clicks", upg1C)))
            upgrade(1);
        if (GuiButton({6, 150, 200, 100}, TextFormat("Upgrade 2: +1 Multi\n\nCost: %d clicks", upg2C)))
            upgrade(2);
        

        DrawText(TextFormat("Clicks: %d", clickCount), 400, 60, 24, RAYWHITE);
        DrawText("made by indpon", (screenWidth / 2) - (MeasureText("made by indpon", 10) / 2), 10, 10, RAYWHITE);

        EndDrawing();
    }
    return 0;
}
