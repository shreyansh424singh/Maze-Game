#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Dot.hpp"
#include "Music.hpp"
// #include "LTexture.hpp"

#include<bits/stdc++.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1000;

//flag=2 initially flag=1 after rules flag=0 after hostel selction
int flag = 2;

Dot* dot1;
Dot* dot2;

Music* MainMusicTrack;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture* gDotTexture;
LTexture* gBackgroundTexture;
LTexture* hostelSelection;
LTexture* mainSelection;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gDotTexture->loadFromFile( "./assets/dot.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	//Load background texture
	if( !gBackgroundTexture->loadFromFile( "./assets/back1.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load hostel selction texture
	if( !hostelSelection->loadFromFile( "./assets/back.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load main selction texture
	if( !mainSelection->loadFromFile( "./assets/back1.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

void mainEvent(SDL_Event& e){
	if(flag!=2) return;
	if( e.type == SDL_KEYDOWN)
		if(e.key.keysym.sym == SDLK_RETURN)
			flag=1;
}

void hostelEvent(SDL_Event& e){
	if(flag!=1) return;
	if( e.type == SDL_KEYDOWN ){
		switch( e.key.keysym.sym )
        {
            case SDLK_j: dot1->setInitialPosition('J'); flag=0; break;
            case SDLK_m: dot1->setInitialPosition('M'); flag=0; break;
            case SDLK_a: dot1->setInitialPosition('A'); flag=0; break;
            case SDLK_k: dot1->setInitialPosition('K'); flag=0; break;
            case SDLK_n: dot1->setInitialPosition('N'); flag=0; break;
            case SDLK_v: dot1->setInitialPosition('V'); flag=0; break;
            case SDLK_s: dot1->setInitialPosition('S'); flag=0; break;
            case SDLK_z: dot1->setInitialPosition('Z'); flag=0; break;
            case SDLK_t: dot1->setInitialPosition('T'); flag=0; break;
            case SDLK_g: dot1->setInitialPosition('G'); flag=0; break;
            case SDLK_u: dot1->setInitialPosition('U'); flag=0; break;
            case SDLK_l: dot1->setInitialPosition('L'); flag=0; break;
            case SDLK_h: dot1->setInitialPosition('H'); flag=0; break;
        }
	}
}

void close()
{
	//Free loaded images
	gDotTexture->free();
    gBackgroundTexture->free();
    hostelSelection->free();
    mainSelection->free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	delete dot1;
	delete dot1;
	delete gDotTexture;
	delete gBackgroundTexture;
	delete hostelSelection;
	delete mainSelection;
}

int main( int argc, char* args[] )
{
////cout<<"main hello \n";

	dot1 = new Dot();
	dot2 = new Dot();

	MainMusicTrack = new Music("./assets/backsound1.mp3");
	MainMusicTrack->PlayMusic(-1);

	gBackgroundTexture = new LTexture();
	gDotTexture = new LTexture();
	hostelSelection = new LTexture();
	mainSelection = new LTexture();

	//Start up SDL and create window
	if( !init() )
	{
////cout<<"if m hu\n";
		printf( "Failed to initialize!\n" );
	}
	else
	{
////cout<<"else m hu\n";
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			//While application is running
			while( !quit ){
				//Handle events on queue
				// while( SDL_PollEvent( &e ) != 0 ){
				// 	//User requests quit
				// 	if( e.type == SDL_QUIT )
				// 		quit = true;

				// 	hostelEvent(e);

				// 	//Handle input for the dot
				// 	dot1->handleEvent( e );
				// 	dot2->handleEventN( e );
				// }

				//Move the dot and check collision
				dot1->move(SCREEN_HEIGHT, SCREEN_WIDTH);
				dot2->move(SCREEN_HEIGHT, SCREEN_WIDTH);

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				if(flag == 2){
					mainSelection->render( 0, 0, gRenderer);
				}

				if(flag == 1){
					hostelSelection->render( 0, 0, gRenderer);
				}

				if(flag == 0){
					//Render background texture to screen
					gBackgroundTexture->render( 0, 0, gRenderer);
	
					//Render dot
					dot1->render(gDotTexture, gRenderer);
					dot2->render(gDotTexture, gRenderer);
				}

				//Update screen
				SDL_RenderPresent( gRenderer );

				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT )
						quit = true;

					mainEvent(e);

					hostelEvent(e);

					//Handle input for the dot
					dot1->handleEvent( e );
					dot2->handleEventN( e );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}