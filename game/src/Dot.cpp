#include "Dot.hpp"
#include<bits/stdc++.h>

using namespace std;

Dot::Dot()
{
cout<<"dotcons \n";

    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

        // vector<int> temp;
    temp = backarray;
cout<<temp.size()<< " size\n";
	for(int j=0; j<1080; j++)
	    for(int i = 0; i<1920; i++)
		    backarr[i][j] = temp[j*1920+i];
}

void Dot::handleEvent( SDL_Event& e )
{
cout<<"handeve \n";

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
cout<<"handeve \n";

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
cout<<"mov \n";

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
	locs[2] = mVelX;
	locs[3] = mVelY;
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
	mVelX = locs[2];
	mVelY = locs[3];
}


void Dot::render(LTexture* gDotTexture, SDL_Renderer*& gRenderer)
{
cout<<"dot render \n";

    //Show the dot
	gDotTexture->render( mPosX, mPosY, gRenderer );
}

bool Dot::checkCollision( SDL_Rect a)
{
cout<<"colli \n";

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

    midX = min((leftA + rightA)/2, 1919);
    midY = min((topA + bottomA)/2, 1079);

// cout<<"midx  " << midX << "   midy   "<<midY<< " value "<<backarr[midX][midY]<<"\n";

    if(backarr[midX][midY] == 1) return true;
    return false;
}