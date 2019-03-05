#include <RoboCatServerPCH.h>
#include <string>

EmojiServer::EmojiServer()
{
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.f;
}


void EmojiServer::Update()
{
	Emoji::Update();
	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
	if (!DoesWantToDie())
	{
		SetLocation(mCat->GetLocation() + yDiff);
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EERS_Pose);
	}
}


void EmojiServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool EmojiServer::HandleCollisionWithCat( RoboCat* inCat )
{
	return false;
}


