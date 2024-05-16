#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Math.h"

/*
    Inputs

        [W] [A] [S] [D] to Move
        [Left Mouse Button] to Shoot

        Scroll Mouse Wheel to Zoom in and out
        Move Mouse to Look Around

        [Esc] to Close Window

        // Debug
        [F1] to Set FPS Limit to 10 FPS
        [F2] to Set FPS Limit to 300 FPS

*/

int main()
{
    srand(time(0));
    Game::Init();
    return 0;
}