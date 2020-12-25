#include <iostream>
#include <cstdlib>     //system("CLS");
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



#include "Game.h"
#include "Graphics.h"
#include "obsticale.h"
#include "enemy.h"
#include "friendly.h"

Game::Game()
{
    init();

    menu();

    killme();
}

Game::~Game(){}

void Game::init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        killme();
    }
     else
    {
        //Create window
        window = SDL_CreateWindow( "Igrca", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

         //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            }


        //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            printf( "SDl_Mixer init failed SDL_Error: %s\n", SDL_GetError() );
        }

        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );
        }

        //renderer init
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            {
                std::cout<<"Renderer creation error"<<std::endl;
                killme();
            }
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    }
}

void Game::killme()
{
    //Destroy window
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    exit(0);
}

void Game::event(bool showval)
{
    if (SDL_PollEvent(&evnt) && showval)
    {
        switch (evnt.type)
            {

            case SDL_QUIT:
                killme();
                break;

            case SDL_MOUSEMOTION:
                std::cout << "X: " <<evnt.motion.x << "  " << "Y: " << evnt.motion.y <<std::endl;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (evnt.button.button)
                {
                case 1:
                    std::cout << "Left button pressed" << std::endl;
                    break;
                case 2:
                    std::cout << "Middle button pressed" << std::endl;
                    break;
                case 3:
                    std::cout << "Right button pressed" << std::endl;
                    break;
                }
                break;

            //*	//Zaznavanje button up
            case SDL_MOUSEBUTTONUP:
                switch (evnt.button.button)
                {
                case 1:
                    std::cout << "Left button released" << std::endl;
                    break;
                case 2:
                    std::cout << "Middle button released" << std::endl;
                    break;
                case 3:
                    std::cout << "Right button released" << std::endl;
                    break;
                }
                break;
            //*/
            }
    }

    if(showval==0)
    {
        if(evnt.type == SDL_QUIT)
            killme();
    }
}

void Game::menu()
{
    Graphics graphics;
    SDL_Rect background; background.w = 800; background.h = 600; background.x = 0; background.y = 0;
    SDL_Texture* backgroundtx = graphics.loadTexture("SpookyMenu.png", renderer);

    Mix_Music *music = NULL;
   // music = Mix_LoadMUS( "SweetSong.wav" );
    if( music == NULL )
    {
        std::cout<< "SDL could not load Music! " << SDL_GetError()<<std::endl;
    }
    else
        Mix_PlayMusic(music, 420);

    SDL_RenderCopy(renderer, backgroundtx, NULL, NULL);
        SDL_RenderPresent(renderer);

    bool click = 0;
    while(1)
    {
        event(0);

        if(click == 0 && evnt.motion.x > 718 && evnt.motion.x < 788 && evnt.motion.y > 12 && evnt.motion.y < 82 && evnt.type == SDL_MOUSEBUTTONDOWN )
        {
            scoreboardizp();
        }
        if(click == 0 && evnt.motion.x > 651 && evnt.motion.x < 774 && evnt.motion.y > 446 && evnt.motion.y < 566 && evnt.type == SDL_MOUSEBUTTONDOWN )
        {
            Lv1();
        }
    }
}

void Game::Lv1()
{
    score =0;
    Graphics graphics;

    SDL_Texture* Background = graphics.loadTexture("Ocean.png", renderer);
    SDL_Texture* obst =  graphics.loadTexture("Mine.png", renderer);
    SDL_Texture* enemytx =  graphics.loadTexture("Kravica.png", renderer);
    SDL_Texture* frietx =  graphics.loadTexture("Friendly_A.png", renderer);

    SDL_Texture* Player = graphics.loadTexture("Player_A.png", renderer);
    SDL_Rect playerrect; playerrect.w = 50; playerrect.h = 50; playerrect.x = 400; playerrect.y = 300;



    obsticale a, b, c, d, e, f;
    enemy e1, e2, e3;
    friendly f1, f2;

    //GAME LOOP
    while(1)
    {

        if(SDL_PollEvent(&evnt)&& evnt.type == SDL_QUIT)
            killme();

        if (evnt.type == SDL_KEYDOWN)
        {
            switch(evnt.key.keysym.sym)
            {
            case SDLK_UP:
                if(playerrect.y>0)
                playerrect.y-=3;
            break;

            case SDLK_DOWN:
                if(playerrect.y<550)
                playerrect.y+=3;
            break;

            case SDLK_RIGHT:
                if(playerrect.x<750)
                playerrect.x+=3;
            break;

            case SDLK_LEFT:
                if(playerrect.x>0)
                playerrect.x-=3;
            break;

            case SDLK_LEFT&&SDLK_UP:
                if(playerrect.x>0)
                playerrect.x-=3;
                playerrect.y-=3;
            break;
            }
        }

        if(a.colplayer(playerrect) || b.colplayer(playerrect) || c.colplayer(playerrect) || d.colplayer(playerrect)|| e.colplayer(playerrect)|| f.colplayer(playerrect)) // ce zadanemo v goro se igra ustavi
            {
                std::cout<< "Opsi! you dead " << std::endl;
                scoreboard();
                break;
            }

            if(f1.colplayer(playerrect) || f2.colplayer(playerrect))
            {

                score = score - 1;
                f1.respawncord();
            }

            if(e1.colplayer(playerrect) || e2.colplayer(playerrect) ||e3.colplayer(playerrect))
        {
            score = score + 1;
            e1.respawncord();
            e2.respawncord();
            e3.respawncord();
        }

        SDL_RenderCopy(renderer, Background, NULL, NULL);

        a.render(renderer, obst);
        b.render(renderer, obst);
        c.render(renderer, obst);
        d.render(renderer, obst);
        e.render(renderer, obst);
        f.render(renderer, obst);

        e1.render(renderer, enemytx, hax);
        e2.render(renderer, enemytx, hax);
        e3.render(renderer, enemytx, hax);

        f1.render(renderer, frietx, hax);

        SDL_RenderCopy(renderer, Player, NULL, &playerrect);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }


}

void Game::scoreboard()
{

    std::ifstream data("score.txt");
    std::ofstream data1("tmp.txt");
    if(data.is_open() && data1.is_open())
    {
        system("CLS");
        std::string ime, str;
        int val;
        bool done = 0;
        std::cout << "Vpisi svoje ime: ";
        std::getline(std::cin, ime);
        while(data >> str >> val)
        {
            if(done == 0 && score > val)
            {
                data1 << ime << " " << score << std::endl;
                data1 << str << " " << val << std::endl;
                done = 1;
            }
            else
            {
                data1 << str << " " << val << std::endl;
            }
        }
        if(done == 0)
        {
            data1 << ime << " " << score << std::endl;
        }

        data.close();
        data1.close();
        remove("score.txt");
        rename("tmp.txt", "score.txt");
    }
    else
    {
        std::ofstream data3("score.txt", std::ios::app);
        if(data3.is_open())
        {
            std::string str;
            system("CLS");
            std::cout << "Vpisi svoje ime: ";
            std::getline(std::cin, str);
            data3 << str << " " << score << std::endl;
            data3.close();
        }

    }
    menu();
}

void Game::scoreboardizp()
{
    system("CLS");
    int counter = 1, val;
    std::string str;
    std::ifstream data("score.txt");
    std::cout << "          SCOREBOARD\n";
    if(data.is_open())
    {
        while(data >> str >> val && counter < 11)
        {
            std::cout << std::right << std::setw(3) << counter << ". " << std::setw(20) << std::left <<  str << " " << val << std::endl;
            counter++;
        }
        data.close();
    }
    else
    {
        std::cout << "\nNo scores\n";
    }
}
