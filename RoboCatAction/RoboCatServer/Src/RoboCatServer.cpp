#include <RoboCatServerPCH.h>

RoboCatServer::RoboCatServer() :
	mCatControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f ),
	mTimeOfNextEmoji(0.f),
	mTimeBetweenEmojis(0.1f)
{}

void RoboCatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void RoboCatServer::Update()
{
	RoboCat::Update();
	
	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
	if( client )
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for( const Move& unprocessedMove : moveList )
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			ProcessInput( deltaTime, currentState );
			SimulateMovement( deltaTime );
		}

		moveList.Clear();
	}
	HandleEmoji();
	HandleShooting();
	

	if( !RoboMath::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		!RoboMath::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}
}

void RoboCatServer::HandleEmoji()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if(emojiIndex > 0)
	{
		//not exact, but okay
		mTimeOfNextEmoji = time + mTimeBetweenEmojis;

		//Emojis!
		EmojiPtr emo = std::static_pointer_cast< Emoji >(GameObjectRegistry::sInstance->CreateGameObject('EMOJ'));
		emo->InitFromShooter(this, emojiIndex);
		SetEmoji(emo);
	}
}

void RoboCatServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		YarnPtr yarn = std::static_pointer_cast< Yarn >(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
		yarn->InitFromShooter(this);
	}
}

void RoboCatServer::SetEmoji(EmojiPtr emo)
{
	if (emoji != nullptr)
	{
		emoji->SetDoesWantToDie(true);
	}
	emoji = emo;
}

void RoboCatServer::TakeDamage( int inDamagingPlayerId )
{
	mHealth--;
	if( mHealth <= 0.f )
	{
		//score one for damaging player...
		ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );

		//and you want to die
		SetDoesWantToDie( true );
		//kill your best friend emoji, that happens sometime
		if (emoji != nullptr)
		{
			emoji->SetDoesWantToDie(true);
		}

		//name of the shooter and target to display on death
		string shooterName = ScoreBoardManager::sInstance->GetEntry(inDamagingPlayerId)->GetPlayerName();
		string targetName = GetPlayerName();
		//sprintf(debugBuffer, "%s . %s \n", shooterName, targetName);
		

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( clientProxy )
		{
			clientProxy->HandleCatDied();
		}


	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}

void RoboCatServer::IncHealth()
{
    if(mHealth < 15)
        mHealth++;
    
    NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}

void RoboCatServer::UpdateSpeed(int value){
    if(mMaxLinearSpeed < 240.f)
        mMaxLinearSpeed += value;

}
