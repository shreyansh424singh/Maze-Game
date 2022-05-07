#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Dot.hpp"
#include "Music.hpp"
#include "DynamicText.hpp"

#include<bits/stdc++.h>

using namespace std;

int usr_id, msock;
int c1, c2, c3=0, r1;
int g0=0, g1=0, g2=0, g3=0, g4=0, g5=0, g6=0;
int interval=0, won=0, los=0;

map<string, pair<int, int>> locations;

//array stores rewards for different locations
int locRewards[33] = {5, 5, 5, 4, 5, 5, 6, 7, 5, 6, 5, 4, 5, 4, 5, 5, 5, 5, 8, 8, 8, 8, 6, 7, 7, 6, 8, 6, 8, 5, 5, 9, 10};

pair<int, int> guards[7] = {make_pair(409, 179), make_pair(302, 207), make_pair(185, 256), make_pair(953, 306), make_pair(933, 600), make_pair(284, 428), make_pair(418, 209) };

//stores all different places
string places[33] = {	"Jwalamukhi        ",
						"Kumaon            ",
						"Aravali           ",
						"Delhi 16          ",
						"Karakoram         ",
						"Nilgiri           ",
						"Safal             ",
						"DMS               ",
						"Nalanda           ",
						"SAC               ",
						"Zanskar           ", 
						"Tennis            ",
						"Shivalik          ",
						"Volleyball        ",
						"Vindhaychal       ",
						"Satpura           ",
						"Girnar            ",
						"Udiagiri          ",
						"Parking           ",
						"Hospital          ",
						"Playground        ",
						"Bharti Building   ",
						"Staff Canteen     ",
						"Library           ",
						"Dogra Hall        ",
						"Blocks            ",
						"Central Workshop  ",
						"LHC               ",
						"Textile Department",
						"Himadri           ",
						"Kailash           ",
						"Guest House       ",
						"Main Market       "};

//Screen dimension constants
const int SCREEN_WIDTH = 1850;
const int SCREEN_HEIGHT = 1000;

//flag=2 initially flag=1 after rules flag=0 after hostel selction
int flag = 2;

Dot* dot1;
Dot* dot2;

Music* MainMusicTrack;
Music* CoinCollect;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//check if enter key is pressed
void mainEvent(SDL_Event& e);

//select hostel
void hostelEvent(SDL_Event& e);

//render images and adds text
void doRender();

//set coordinates of destinations initially
void assign();

//generates new random destination for players
void randomLocation();

void gaurdRen(int n);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture* gDotTexture;
LTexture* gDotTexture1;
LTexture* gGaurdTexture;
LTexture* gBackgroundTexture;
LTexture* hostelSelection;
LTexture* mainSelection;
LTexture* intervalScreen;
LTexture* wonScreen;
LTexture* lostScreen;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "<<< Mumbo-Jumbo >>>", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
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
	if( !gDotTexture->loadFromFile( "./assets/Images/Dot0.png", gRenderer ) ){
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load press texture
	if( !gDotTexture1->loadFromFile( "./assets/Images/Dot1.png", gRenderer ) ){
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load press texture
	if( !gGaurdTexture->loadFromFile( "./assets/Images/guard.png", gRenderer ) ){
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	//Load background texture
	if( !gBackgroundTexture->loadFromFile( "./assets/Images/Game_Back.png", gRenderer ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load hostel selction texture
	if( !hostelSelection->loadFromFile( "./assets/Images/Menu.png", gRenderer ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load main selction texture
	if( !mainSelection->loadFromFile( "./assets/Images/Load_Screen.png", gRenderer ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load interval texture
	if( !intervalScreen->loadFromFile( "./assets/Images/GameInterval.png", gRenderer ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load won texture
	if( !wonScreen->loadFromFile( "./assets/Images/Won.png", gRenderer ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load lost texture
	if( !lostScreen->loadFromFile( "./assets/Images/Lost.png", gRenderer ) ){
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
            case SDLK_j: dot1->setInitialPosition('J'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_m: dot1->setInitialPosition('M'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_a: dot1->setInitialPosition('A'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_k: dot1->setInitialPosition('K'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_n: dot1->setInitialPosition('N'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_v: dot1->setInitialPosition('V'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_s: dot1->setInitialPosition('S'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_z: dot1->setInitialPosition('Z'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_t: dot1->setInitialPosition('T'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_g: dot1->setInitialPosition('G'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_u: dot1->setInitialPosition('U'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_l: dot1->setInitialPosition('L'); dot1->ready=1; flag=0; randomLocation(); break;
            case SDLK_h: dot1->setInitialPosition('H'); dot1->ready=1; flag=0; randomLocation(); break;
        }
	}
	dot1->sendPos(usr_id, msock);
	dot2->getPos(usr_id, msock);
}


void doRender(){

	if(flag == 2){
		mainSelection->render( 0, 0, gRenderer);
	}

	if(flag == 1){
		hostelSelection->render( 0, 0, gRenderer);
	}

	if(flag == 0){

		if(won == 1){
			wonScreen->render( 0, 0, gRenderer);
		}
		else if(los == 1){
			lostScreen->render( 0, 0, gRenderer);
		}
		else if(dot1->intervalFlag == 1){
			intervalScreen->render( 0, 0, gRenderer);
			c3--;
			if(c3 == 0) {
				randomLocation();
				dot1->intervalFlag = 0;
			}
		}
		else{
			//Render background texture to screen
			gBackgroundTexture->render( 0, 0, gRenderer);

			if(g0 == 1){
				gGaurdTexture->render( guards[0].first, guards[0].second, gRenderer );
			}
			if(g1 == 1){
				gGaurdTexture->render( guards[1].first, guards[1].second, gRenderer );
			}
			if(g2 == 1){
				gGaurdTexture->render( guards[2].first, guards[2].second, gRenderer );
			}
			if(g3 == 1){
				gGaurdTexture->render( guards[3].first, guards[3].second, gRenderer );
			}
			if(g4 == 1){
				gGaurdTexture->render( guards[4].first, guards[4].second, gRenderer );
			}
			if(g5 == 1){
				gGaurdTexture->render( guards[5].first, guards[5].second, gRenderer );
			}
			if(g6 == 1){
				gGaurdTexture->render( guards[6].first, guards[6].second, gRenderer );
			}

			//Render dot
			if(usr_id == 0) {
				dot1->render(gDotTexture, gRenderer);
				dot2->render(gDotTexture1, gRenderer);
			} else {
				dot1->render(gDotTexture1, gRenderer);
				dot2->render(gDotTexture, gRenderer);
			}

			//Render Text
			DynamicText text("./assets/fonts/alba.ttf",32);
			
			if(dot1->mYOn == 1)  text.DrawText(gRenderer,"Yulu Activated",575,632,240,100);
			text.DrawText(gRenderer,"Destination : ",575,702,200,100);
			text.DrawText(gRenderer,places[r1],780,702,300,100);
			text.DrawText(gRenderer,"Time : ",575,772,150,100);
			text.DrawText(gRenderer,to_string(c2),715,782,60,85);
			text.DrawText(gRenderer,"Yulu Left : ",855,772,180,100);
			text.DrawText(gRenderer,to_string(dot1->mYulu),1035,782,40,85);
			if(dot1->mDestReached == 1) text.DrawText(gRenderer,"You Reached",575,892,200,100);
			if(dot2->mDestReached == 1) text.DrawText(gRenderer,"Opponent Reached",775,892,200,100);
			text.DrawText(gRenderer,"Your Score : ",1200,697,200,100);
			text.DrawText(gRenderer,to_string(dot1->mScore),1270,757,60,100);
			text.DrawText(gRenderer,"Opponent Score : ",1200,827,200,100);
			text.DrawText(gRenderer,to_string(dot2->mScore),1270,892,60,100);
		}
	}

}

void assign(){
	locations["Jwalamukhi        "] = make_pair(171, 55);
	locations["Kumaon            "] = make_pair(228, 81);
	locations["Aravali           "] = make_pair(151, 174);
	locations["Delhi 16          "] = make_pair(213, 203);
	locations["Karakoram         "] = make_pair(135, 311);
	locations["Nilgiri           "] = make_pair(128, 439);
	locations["Safal             "] = make_pair(120, 602);
	locations["DMS               "] = make_pair(227, 891);
	locations["Nalanda           "] = make_pair(244, 512);
	locations["SAC               "] = make_pair(346, 411);
	locations["Zanskar           "] = make_pair(349, 314);
	locations["Tennis            "] = make_pair(287, 259);
	locations["Shivalik          "] = make_pair(334, 241);
	locations["Volleyball        "] = make_pair(274, 179);
	locations["Vindhaychal       "] = make_pair(324, 89);
	locations["Satpura           "] = make_pair(464, 85);
	locations["Girnar            "] = make_pair(551, 117);
	locations["Udiagiri          "] = make_pair(575, 75);
	locations["Parking           "] = make_pair(481, 461);
	locations["Hospital          "] = make_pair(563, 345);
	locations["Playground        "] = make_pair(679, 472);
	locations["Bharti Building   "] = make_pair(741, 351);
	locations["Staff Canteen     "] = make_pair(832, 496);
	locations["Library           "] = make_pair(858, 350);
	locations["Dogra Hall        "] = make_pair(881, 324);
	locations["Blocks            "] = make_pair(864, 220);
	locations["Central Workshop  "] = make_pair(945, 442);
	locations["LHC               "] = make_pair(1016, 440);
	locations["Textile Department"] = make_pair(1026, 315);
	locations["Himadri           "] = make_pair(1270, 88);
	locations["Kailash           "] = make_pair(1226, 184);
	locations["Guest House       "] = make_pair(1402, 196);
	locations["Main Market       "] = make_pair(1423, 372);
}

void randomLocation(){
	r1 = rand()%33;

	MainMusicTrack->PlayMusic(-1);

	//new destination should not be same as old destination
	while(dot1->mDestX == locations[places[r1]].first && dot1->mDestY == locations[places[r1]].second 
	   && abs(dot1->returnX() - locations[places[r1]].first) <= 50 && abs(dot1->returnY() - locations[places[r1]].second) <= 50 ) {
		r1 = rand()%33;
	}

	if(r1%2==0){
		gaurdRen(r1%7);
	}
	if(r1%3==0){
		gaurdRen((r1/5)%7);
	}
	if(r1%5==0){
		gaurdRen((r1/11)%7);
	}

	//set rewards 
	dot1->myReward = locRewards[r1];

	//set destination positions
	dot1->mDestX = locations[places[r1]].first;
	dot1->mDestY = locations[places[r1]].second;

	//time counters
	c1=c2=0;

	//Yulu off at start
	dot1->mYOn = 0;
}

void gaurdRen(int n){
	switch(n){
		case 0: g0=1; break;
		case 1: g1=1; break;
		case 2: g2=1; break;
		case 3: g3=1; break;
		case 4: g4=1; break;
		case 5: g5=1; break;
		case 6: g6=1; break;
	}
}

void close()
{
	//Free loaded images
	gGaurdTexture->free();
	gDotTexture->free();
	gDotTexture1->free();
    gBackgroundTexture->free();
    hostelSelection->free();
    mainSelection->free();
	intervalScreen->free();
	wonScreen->free();
	lostScreen->free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//delete pointers
	delete dot1;
	delete dot1;
	delete gGaurdTexture;
	delete gDotTexture;
	delete gDotTexture1;
	delete gBackgroundTexture;
	delete hostelSelection;
	delete mainSelection;
	delete intervalScreen;
	delete lostScreen;
	delete wonScreen;
	delete MainMusicTrack;
	delete CoinCollect;

	//close socket
	close(msock);
}

int main( int argc, char* args[] ){

	//for seeding
	unsigned int time_ui = (unsigned int) time(NULL);

	cout<<"Enter 0 for Server, 1 for client: \n";
	cin>>usr_id;
	if(usr_id == 0) {
		srand( time_ui*5 );
		msock = connect_server();
	}
	else {
		srand( time_ui*3 );
		string s;
		cout<<"Enter ip of server: \n";
		cin>>s;
		char* char_arr;
		char_arr = &s[0];
		msock = connect_client(char_arr);

	}

	dot1 = new Dot();
	dot2 = new Dot();

	MainMusicTrack = new Music("./assets/Sounds/backsound1.mp3");
	MainMusicTrack->SetVolume(39);
	// MainMusicTrack->PlayMusic(-1);
	
	CoinCollect = new Music("./assets/Sounds/coin.wav");

	gBackgroundTexture = new LTexture();
	gGaurdTexture = new LTexture();
	gDotTexture = new LTexture();
	gDotTexture1 = new LTexture();
	hostelSelection = new LTexture();
	mainSelection = new LTexture();
	intervalScreen = new LTexture();
	lostScreen = new LTexture();
	wonScreen = new LTexture();

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			assign();

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			//While application is running
			while( !quit ){

				//check if game is ended
				if(dot2->mScore < 1) 
					if(los==0) won=1;
				if(dot1->mScore < 1) 
					if(won==0) los=1;
				
				//move the players
				dot1->move(SCREEN_HEIGHT, SCREEN_WIDTH, usr_id, msock);
				dot2->move_P2(usr_id, msock);

				//check collision with gaurd
				if(g0 == 1 && abs(guards[0].first - dot1->returnX()) < 13 &&  abs(guards[0].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g0=0;}
				if(g1 == 1 && abs(guards[1].first - dot1->returnX()) < 13 &&  abs(guards[1].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g1=0;}
				if(g2 == 1 && abs(guards[2].first - dot1->returnX()) < 13 &&  abs(guards[2].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g2=0;}
				if(g3 == 1 && abs(guards[3].first - dot1->returnX()) < 13 &&  abs(guards[3].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g3=0;}
				if(g4 == 1 && abs(guards[4].first - dot1->returnX()) < 13 &&  abs(guards[4].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g4=0;}
				if(g5 == 1 && abs(guards[5].first - dot1->returnX()) < 13 &&  abs(guards[5].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g5=0;}
				if(g6 == 1 && abs(guards[6].first - dot1->returnX()) < 13 &&  abs(guards[6].second - dot1->returnY()) < 13) {dot1->mScore -= 20; g6=0;}

				//wait till both players are ready
				if(dot2->ready == 1 && dot1->ready == 1) {
					c1++;
					if(c1==45){
						c1=0; c2++;
						if(dot1->mDestReached == 0) dot1->mScore -= (2-dot1->mYOn);
					}

					//check if player reached destination
					bool ch1 = dot1->checkDestReached();
					if(ch1 == 1) {
						CoinCollect->PlayMusic(1);
					}

					//if both players reached destinations
					if(dot1->mDestReached == 1 && dot2->mDestReached == 1){

						//show interval screen
						dot1->intervalFlag = 1;
						if(c3==0) c3 = 45*5;

						dot1->sendPos(usr_id, msock);
						dot2->getPos(usr_id, msock);

						dot1->mDestReached = 0;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				doRender();

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT )
						quit = true;

					//Handle input for start screen
					mainEvent(e);

					//Handle input for hostel selection screen
					hostelEvent(e);

					//Handle input for the dot
					dot1->handleEvent( e );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}