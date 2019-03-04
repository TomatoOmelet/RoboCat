#include <RoboCatServerPCH.h>


EmojiServer::EmojiServer()
{

}


void EmojiServer::Update()
{
	Emoji::Update();
}

bool EmojiServer::HandleCollisionWithCat( RoboCat* inCat )
{
	return false;
}


