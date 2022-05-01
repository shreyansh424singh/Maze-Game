#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Dot.hpp"
// #include "LTexture.hpp"

#include<bits/stdc++.h>

using namespace std;

int usr_id, msock;

//Screen dimension constants
const int SCREEN_WIDTH = 1920/2;
const int SCREEN_HEIGHT = 1080/2;

Dot* dot1;
Dot* dot2;

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
	if( !gBackgroundTexture->loadFromFile( "./assets/back.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture->free();
    gBackgroundTexture->free();

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
}

int main( int argc, char* args[] )
{
	std::cout<<"Enter 0 for Server, 1 for client: \n";
	std::cin>>usr_id;
	if(usr_id == 0) {
		msock = connect_server();
	}
	else {
		string s;
		std::cout<<"Enter ip of server: \n";
		std::cin>>s;
		char* char_arr;
		char_arr = &s[0];
		msock = connect_client(char_arr);
	}
cout<<"main hello \n";

dot1 = new Dot();
dot2 = new Dot();

gBackgroundTexture = new LTexture();
gDotTexture = new LTexture();

	//Start up SDL and create window
	if( !init() )
	{
cout<<"if m hu\n";
		printf( "Failed to initialize!\n" );
	}
	else
	{
cout<<"else m hu\n";
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

cout<<"refer\n";

			//The dot that will be moving around on the screen
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot1->handleEvent( e );
					// dot2->handleEventN( e );
				}

				//Move the dot and check collision
				dot1->move(SCREEN_HEIGHT, SCREEN_WIDTH, usr_id, msock);
				dot2->move_P2(usr_id, msock);

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
				gBackgroundTexture->render( 0, 0, gRenderer);

				//Render dot
				dot1->render(gDotTexture, gRenderer);
				dot2->render(gDotTexture, gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}