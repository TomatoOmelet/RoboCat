#include <RoboCatPCH.h>

Emoji::Emoji() :
	mMuzzleSpeed( 3.f ),
	mPlayerId( 0 )
{
	SetScale( GetScale() * 0.25f );
	SetCollisionRadius( 0.125f );
}



uint32_t Emoji::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EERS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= EERS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EERS_Texture)
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EERS_Texture;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EERS_PlayerId )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( mPlayerId, 8 );

		writtenState |= EERS_PlayerId;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}




	return writtenState;
}



bool Emoji::HandleCollisionWithCat( RoboCat* inCat )
{
	( void ) inCat;

	//you hit a cat, so look like you hit a cat
	


	return false;
}


void Emoji::InitFromShooter( RoboCat* inShooter, int index)
{
	SetLocation(inShooter->GetLocation() + yDiff);
	SetPlayerId(inShooter->GetPlayerId());
	SetCat(inShooter);
	ChangeTexture(index);
}

void Emoji::Update()
{
	//we'll let the cats handle the collisions
}
