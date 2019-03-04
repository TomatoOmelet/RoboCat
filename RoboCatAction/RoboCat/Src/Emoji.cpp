#include <RoboCatPCH.h>

Emoji::Emoji() :
	mMuzzleSpeed( 3.f ),
	mVelocity( Vector3::Zero ),
	mPlayerId( 0 )
{
	SetScale( GetScale() * 0.25f );
	SetCollisionRadius( 0.125f );
}



uint32_t Emoji::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EYRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		Vector3 velocity = GetVelocity();
		inOutputStream.Write( velocity.mX );
		inOutputStream.Write( velocity.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= EYRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_Color )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EYRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_PlayerId )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( mPlayerId, 8 );

		writtenState |= EYRS_PlayerId;
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


void Emoji::InitFromShooter( RoboCat* inShooter )
{
	SetColor( inShooter->GetColor() );
	SetPlayerId( inShooter->GetPlayerId() );

	Vector3 forward = inShooter->GetForwardVector();
	SetLocation( inShooter->GetLocation() /* + forward * 0.55f */ );

}

void Emoji::Update()
{
	
	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetLocation( GetLocation() + mVelocity * deltaTime );
	

	//we'll let the cats handle the collisions
}
