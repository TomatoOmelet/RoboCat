#include <RoboCatClientPCH.h>

EmojiClient::EmojiClient()
{
	mSpriteComponent.reset( new SpriteComponent( this ) );
	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "angry" ) );
}

void EmojiClient::ChangeTexture(int index)
{
	switch (index)
	{
	case 0:
		{
			mSpriteComponent.reset(new SpriteComponent(this));
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("smile"));
			break;
		}
	case 1:
		{
			mSpriteComponent.reset(new SpriteComponent(this));
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("angry"));
			break;
		}
	default:
		{
			mSpriteComponent.reset(new SpriteComponent(this));
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("cry"));
			break;
		}
	}
}

void EmojiClient::Read( InputMemoryBitStream& inInputStream )
{
	bool stateBit;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		Vector3 location;
		inInputStream.Read( location.mX );
		inInputStream.Read( location.mY );
		SetLocation( location );

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

	inInputStream.Read( stateBit );
	if( stateBit )
	{	
		inInputStream.Read( mPlayerId, 8 );
	}

}
