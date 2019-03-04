//
//  MilkServer.cpp
//  RoboCatActionServer
//
//  Created by Xavier Chua on 2/28/19.
//
#include <RoboCatServerPCH.h>

MilkServer::MilkServer()
{
    mTimeToDie = Timing::sInstance.GetFrameStartTime() + (RoboMath::GetRandomFloat() * 20.f);
}

void MilkServer::HandleDying()
{
    NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


bool MilkServer::HandleCollisionWithCat( RoboCat* inCat )
{
    //kill yourself!
    SetDoesWantToDie( true );
    
    ScoreBoardManager::sInstance->IncScore( inCat->GetPlayerId(), 1 );
    
    static_cast< RoboCatServer* >( inCat )->IncHealth();
    static_cast< RoboCatServer* >( inCat )->UpdateSpeed(10);
    
    return false;
}

void MilkServer::Update() {
    
    if( Timing::sInstance.GetFrameStartTime() > mTimeToDie )
    {
        SetDoesWantToDie( true );
    }
}
