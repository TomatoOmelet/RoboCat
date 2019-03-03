#include <RoboCatServerPCH.h>

const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

MouseServer::MouseServer()
{
}

void MouseServer::Update()
{
	Mouse::Update();
	ProcessCollisionsWithScreenWalls();
}

uint32_t MouseServer::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	LOG("Server Sent", 0);
	return Mouse::Write(inOutputStream, inDirtyState);
}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


bool MouseServer::HandleCollisionWithCat( RoboCat* inCat )
{
	//kill yourself!
	SetDoesWantToDie( true );

	ScoreBoardManager::sInstance->IncScore( inCat->GetPlayerId(), 1 );

	return false;
}


