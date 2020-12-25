#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

class Game
{
    public:
        Game();
       ~Game();
        void killme();
        void init();
        void menu();
        void event(bool showval);
        SDL_Renderer* renderer;
        void Lv1();
        bool hax=0;
        int score=0;
        void scoreboardizp();
        void scoreboard();
    private:

        int SCREEN_WIDTH = 800;
        int SCREEN_HEIGHT = 600;
         //The window we'll be rendering to
        SDL_Window* window = NULL;
        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;
        //Event handler
        SDL_Event evnt;


};

#endif // GAME_H
