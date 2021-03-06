#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<bits/stdc++.h>

#include "LTexture.hpp"
#include "server.h"
#include "client.h"
#include "Maparray.h"

using namespace std;

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		// Readiness
		int ready, myReward, intervalFlag;

		//Maximum axis velocity of the dot
		int DOT_VEL = 1;

		// Score, yulu
		int mScore, mYulu;

		int mDestX, mDestY, mDestReached, mYOn;

        vector<int> temp;
        int backarr[1920][1080];

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move(int SCREEN_HEIGHT, int SCREEN_WIDTH, int usr_id, int sys_sock);
		void move_P2(int usr_id, int sys_sock);

		void sendPos(int usr_id, int msock);
		void getPos(int usr_id, int msock);

		//Shows the dot on the screen
		void render(LTexture* gDotTexture, SDL_Renderer*& gRenderer);

		//check collision with road
        bool checkCollision( SDL_Rect a);

		//set initial position as per initial position
		void setInitialPosition(char p);

		//check if player reached destination
		bool checkDestReached();

		int returnX();
		int returnY();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		
		//Dot's collision box
		SDL_Rect mCollider;
};