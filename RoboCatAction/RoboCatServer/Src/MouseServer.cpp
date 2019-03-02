#include <RoboCatServerPCH.h>
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

MouseServer::MouseServer()
{
}

void MouseServer::Update()
{
	Mouse::Update();
	ProcessCollisionsWithScreenWalls();
}

void MouseServer::ProcessCollisionsWithScreenWalls()
{
	Vector3 location = GetLocation();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	float radius = GetCollisionRadius();

	//if the mouse collides against a wall, change direction
	if ((y + radius) >= HALF_WORLD_HEIGHT && vy > 0)
	{
		mVelocity.mY = -vy;// * mWallRestitution;
		location.mY = HALF_WORLD_HEIGHT - radius;
		SetLocation(location);
	}
	else if (y <= (-HALF_WORLD_HEIGHT - radius) && vy < 0)
	{
		mVelocity.mY = -vy;// * mWallRestitution;
		location.mY = -HALF_WORLD_HEIGHT - radius;
		SetLocation(location);
	}

	if ((x + radius) >= HALF_WORLD_WIDTH && vx > 0)
	{
		mVelocity.mX = -vx;// *mWallRestitution;
		location.mX = HALF_WORLD_WIDTH - radius;
		SetLocation(location);
	}
	else if (x <= (-HALF_WORLD_WIDTH - radius) && vx < 0)
	{
		mVelocity.mX = -vx; //*mWallRestitution;
		location.mX = -HALF_WORLD_WIDTH - radius;
		SetLocation(location);
	}

}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


bool MouseServer::HandleCollisionWithCat( RoboCat* inCat )
{
	//kill yourself!
	SetDoesWantToDie( true );

	ScoreBoardManager::sInstance->IncScore( inCat->GetPlayerId(), 1 );

	return false;
}


