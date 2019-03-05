#include <RoboCatServerPCH.h>
#include <string>

EmojiServer::EmojiServer()
{

}


void EmojiServer::Update()
{
	Emoji::Update();

	//die when cat doesn't exist, otherwise update and following cat
	try
	{
		SetLocation(mCat->GetLocation() + yDiff);
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EERS_Pose);
	}
	catch (const std::exception&){
		SetDoesWantToDie(true);
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


