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
    string s = "Death Log Manager";
    mEntries.push_front(s);
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
        //printf("\n%s has been removed from deathlog\n", s.c_str());
        return true;
    }
    
    return false;
}

void DeathLogManager::AddEntry( string deathLog )
{
    RemoveEntry( );
    
    mEntries.push_back( deathLog );
    //printf("%s added to the stack\n", deathLog.c_str());
}

bool DeathLogManager::Write( OutputMemoryBitStream& inOutputStream ) const
{
    if(!mEntries.empty()) {
        string log = mEntries.front();
        
        inOutputStream.Write( log );
    }
    
    return true;
}



bool DeathLogManager::Read( InputMemoryBitStream& inInputStream )
{
    bool didSucceed = true;
    if(!mEntries.empty()) {
        string log;
        
        inInputStream.Read( log );
        if (didSucceed) {
            AddEntry(log);
        }
    }
    //just replace everything that's here, it don't matter...
    
    return true;
}





