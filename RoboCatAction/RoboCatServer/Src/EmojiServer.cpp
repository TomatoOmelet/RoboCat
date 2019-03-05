#include <RoboCatServerPCH.h>
#include <string>

EmojiServer::EmojiServer()
{

}


void EmojiServer::Update()
{
	Emoji::Update();
	SetLocation(mCat->GetLocation() + yDiff);
	LOG(std::to_string(GetLocation().mX).c_str(), 0);
}

bool EmojiServer::HandleCollisionWithCat( RoboCat* inCat )
{
	return false;
}


