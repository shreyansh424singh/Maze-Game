// g++ main.cpp -w -lSDL2 -lSDL2_image -o a.out && ./a.out

#include<SDL2/SDL.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main( int argc, char* args[] ){

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    return 0;
}