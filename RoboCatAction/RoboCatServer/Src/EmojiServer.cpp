#include <RoboCatServerPCH.h>
#include <string>

EmojiServer::EmojiServer()
{

}


void EmojiServer::Update()
{
	Emoji::Update();
	SetLocation(mCat->GetLocation() + yDiff);
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EERS_Pose);
}

bool EmojiServer::HandleCollisionWithCat( RoboCat* inCat )
{
	return false;
}


