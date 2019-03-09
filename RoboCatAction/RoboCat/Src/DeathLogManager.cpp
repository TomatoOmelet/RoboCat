//
//  DeathLogManager.cpp
//  RoboCatAction
//
//  Created by Xavier Chua on 3/8/19.
//

#include "RoboCatPCH.h"

std::unique_ptr< DeathLogManager >    DeathLogManager::sInstance;


void DeathLogManager::StaticInit()
{
    sInstance.reset( new DeathLogManager() );
}

DeathLogManager::DeathLogManager()
{

}

string DeathLogManager::GetEntry( )
{
    if (!mEntries.empty())
    {
        return mEntries.front();
        
    }
    
    return nullptr;
}

bool DeathLogManager::RemoveEntry( )
{
    if(!mEntries.empty())
    {
        string s = mEntries.front();
        mEntries.pop_front();
        printf("\n%s has been removed from deathlog\n", s.c_str());
        return true;
    }
    
    return false;
}

void DeathLogManager::AddEntry( string deathLog )
{
    //if this player id exists already, remove it first- it would be crazy to have two of the same id
    RemoveEntry( );
    
    mEntries.push_back( deathLog );
    printf("%s added to the stack\n", deathLog.c_str());
}

bool DeathLogManager::Write( OutputMemoryBitStream& inOutputStream ) const
{
    //we don't know our player names, so it's hard to check for remaining space in the packet...
    //not really a concern now though
    if(!mEntries.empty()) {
        string log = mEntries.front();
        
        inOutputStream.Write( log );
    }
    
    return true;
}



bool DeathLogManager::Read( InputMemoryBitStream& inInputStream )
{
    if(!mEntries.empty()) {
        string log = mEntries.front();
        
        inInputStream.Read( log );
    }
    //just replace everything that's here, it don't matter...
    
    return true;
}





