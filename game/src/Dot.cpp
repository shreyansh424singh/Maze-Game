#include "Dot.hpp"
#include<bits/stdc++.h>

using namespace std;

Dot::Dot()
{

    //Initialize the offsets
    // setInitialPosition(p);
    ready = 0;

    mPosX = 540;
    mPosY = 105;

    mScore = 100;
    mYulu = 3;

    mDestReached = 0;
    mDestX = 346;
    mDestY = 411;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

        // vector<int> temp;
    temp = backarray;
	for(int j=0; j<1000; j++)
	    for(int i = 0; i<1600; i++)
		    backarr[i][j] = temp[j*1600+i];
}

void Dot::handleEvent( SDL_Event& e )
{

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::handleEventN( SDL_Event& e )
{

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY -= DOT_VEL; break;
            case SDLK_s: mVelY += DOT_VEL; break;
            case SDLK_a: mVelX -= DOT_VEL; break;
            case SDLK_d: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY += DOT_VEL; break;
            case SDLK_s: mVelY -= DOT_VEL; break;
            case SDLK_a: mVelX += DOT_VEL; break;
            case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(int SCREEN_HEIGHT, int SCREEN_WIDTH, int usr_id, int sys_sock)
{

    //Move the dot left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider) )
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
	mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider) )
    {
        //Move back
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
    int* locs = new int(5);
	locs[0] = mPosX;
	locs[1] = mPosY;
	locs[2] = mDestReached;
	locs[3] = mScore;
    locs[4] = ready;
	if(usr_id == 0) {
		server_send_data(sys_sock, locs);
	}
	else {
		client_send_data(sys_sock, locs);
	}
}

void Dot::move_P2(int usr_id, int sys_sock)
{
	int* locs = new int(5);
	if(usr_id == 0) {
		server_recv_data(sys_sock, locs);
	}
	else {
		client_recv_data(sys_sock, locs);
	}

	mPosX = locs[0];
	mPosY = locs[1];
	mDestReached = locs[2];
	mScore = locs[3];
    ready = locs[4];
}

void Dot::getPos(int usr_id, int sys_sock)
{
	int* locs = new int(5);
	if(usr_id == 0) {
		server_recv_data(sys_sock, locs);
	}
	else {
		client_recv_data(sys_sock, locs);
	}

	mPosX = locs[0];
	mPosY = locs[1];
    mDestReached = locs[2];
	mScore = locs[3];
    ready = locs[4];

	// mVelX = locs[2];
	// mVelY = locs[3];
    // mScore = locs[4];
}


void Dot::sendPos(int usr_id, int sys_sock)
{
    int* locs = new int(5);
	locs[0] = mPosX;
	locs[1] = mPosY;
    locs[2] = mDestReached;
	locs[3] = mScore;
    locs[4] = ready;

	// locs[2] = mVelX;
	// locs[3] = mVelY;
    // locs[4] = mScore;
	if(usr_id == 0) {
		server_send_data(sys_sock, locs);
	}
	else {
		client_send_data(sys_sock, locs);
	}
}



void Dot::render(LTexture* gDotTexture, SDL_Renderer*& gRenderer)
{

    //Show the dot
	gDotTexture->render( mPosX, mPosY, gRenderer );
}

bool Dot::checkCollision( SDL_Rect a)
{

    //The sides of the rectangles
    int leftA;
    int rightA;
    int topA;
    int bottomA;
    int midX, midY;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    midX = min((leftA + rightA)/2, 1599);
    midY = min((topA + bottomA)/2, 999);

// 
    if(backarr[midX][midY] == 1) return true;
    return false;
}

void Dot::setInitialPosition(char p){
    switch(p){
        case 'J': mPosX = 161; mPosY = 45; break;
        case 'M': mPosX = 220; mPosY = 70; break;
        case 'A': mPosX = 140; mPosY = 168; break;
        case 'K': mPosX = 125; mPosY = 306; break;
        case 'N': mPosX = 118; mPosY = 426; break;
        case 'V': mPosX = 314; mPosY = 79; break;
        case 'S': mPosX = 324; mPosY = 230; break;
        case 'Z': mPosX = 340; mPosY = 301; break;
        case 'T': mPosX = 453; mPosY = 75; break;
        case 'G': mPosX = 541; mPosY = 105; break;
        case 'U': mPosX = 565; mPosY = 65; break;
        case 'L': mPosX = 1216; mPosY = 174; break;
        case 'H': mPosX = 1264; mPosY = 84; break;
    }
}

bool Dot::checkDestReached(){
    if(abs(mDestX-mPosX) <= 10 && abs(mDestY-mPosY) <= 10){

//play sound

        //make reached = 1 
        mDestReached = 1;
        return true;
    }
    return false;
}
