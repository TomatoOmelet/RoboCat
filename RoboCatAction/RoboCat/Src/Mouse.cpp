#include <RoboCatPCH.h>
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

Mouse::Mouse()
{
	SetScale( GetScale() * 0.5f );
	SetCollisionRadius( 0.25f );
	Vector3 minVelocity = Vector3(-1, -1, 0);
	Vector3 maxVelocity = Vector3(1, 1, 0);
	SetVelocity(RoboMath::GetRandomVector(minVelocity, maxVelocity));
}

void Mouse::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SetLocation(GetLocation() + GetVelocity() * deltaTime);
	//ProcessCollisionsWithScreenWalls();
}

void Mouse::ProcessCollisionsWithScreenWalls()
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

bool Mouse::HandleCollisionWithCat( RoboCat* inCat )
{
	( void ) inCat;
	return false;
}




uint32_t Mouse::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EMRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		Vector3 velocity = GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		inOutputStream.Write( GetRotation() );

		writtenState |= EMRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EMRS_Color )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EMRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}


	return writtenState;
}

void Mouse::Read( InputMemoryBitStream& inInputStream )
{
	bool stateBit;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		Vector3 location;
		inInputStream.Read( location.mX );
		inInputStream.Read( location.mY );
		SetLocation( location );

		Vector3 velocity;
		inInputStream.Read(velocity.mX);
		inInputStream.Read(velocity.mY);
		SetVelocity(velocity);

		float rotation;
		inInputStream.Read( rotation );
		SetRotation( rotation );
	}


	inInputStream.Read( stateBit );
	if( stateBit )
	{	
		Vector3 color;
		inInputStream.Read( color );
		SetColor( color );
	}
}

