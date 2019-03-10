#include "RoboCatPCH.h"

std::unique_ptr< ScoreBoardManager >	ScoreBoardManager::sInstance;


void ScoreBoardManager::StaticInit()
{
	sInstance.reset( new ScoreBoardManager() );
}

ScoreBoardManager::ScoreBoardManager()
{
	mDefaultColors.push_back( Colors::LightYellow );
	mDefaultColors.push_back( Colors::LightBlue );
	mDefaultColors.push_back( Colors::LightPink );
	mDefaultColors.push_back( Colors::LightGreen );
}

ScoreBoardManager::Entry::Entry( uint32_t inPlayerId, const string& inPlayerName, const Vector3& inColor ) :
mPlayerId( inPlayerId ),
mPlayerName( inPlayerName ),
mColor( inColor )
{
	SetStats( 0, 0, 0 );
}

void ScoreBoardManager::Entry::SetStats( int32_t inScore, int32_t inKills, int32_t inDeaths )
{
	mScore = inScore;
    mKills = inKills;
    mDeaths = inDeaths;

	char	buffer[ 256 ];
	snprintf( buffer, 256, "%s %i/%i -- %i", mPlayerName.c_str(), mKills, mDeaths, mScore );
	mFormattedNameScore = string( buffer );

}

ScoreBoardManager::Entry* ScoreBoardManager::GetEntry( uint32_t inPlayerId )
{
	for ( Entry &entry: mEntries )
	{
		if( entry.GetPlayerId() == inPlayerId )
		{
			return &entry;
		}
	}

	return nullptr;
}

bool ScoreBoardManager::RemoveEntry( uint32_t inPlayerId )
{
	for( auto eIt = mEntries.begin(), endIt = mEntries.end(); eIt != endIt; ++eIt )
	{
		if( ( *eIt ).GetPlayerId() == inPlayerId )
		{
			mEntries.erase( eIt );
			return true;
		}
	}

	return false;
}

void ScoreBoardManager::AddEntry( uint32_t inPlayerId, const string& inPlayerName )
{
	//if this player id exists already, remove it first- it would be crazy to have two of the same id
	RemoveEntry( inPlayerId );
	
	mEntries.emplace_back( inPlayerId, inPlayerName, mDefaultColors[ inPlayerId % mDefaultColors.size() ] );
}

void ScoreBoardManager::IncScore( uint32_t inPlayerId, int inAmount )
{
	Entry* entry = GetEntry( inPlayerId );
	if( entry )
	{
		entry->SetStats( entry->GetScore() + inAmount, entry->GetPlayerKills(), entry->GetPlayerDeaths() );
	}
}

void ScoreBoardManager::IncKills( uint32_t inPlayerId, int inAmount )
{
    Entry* entry = GetEntry( inPlayerId );
    if( entry )
    {
        entry->SetStats(entry->GetScore(), entry->GetPlayerKills() + inAmount, entry->GetPlayerDeaths() );
    }
}

void ScoreBoardManager::IncDeaths( uint32_t inPlayerId, int inAmount )
{
    Entry* entry = GetEntry( inPlayerId );
    if( entry )
    {
        entry->SetStats(entry->GetScore(), entry->GetPlayerKills(), entry->GetPlayerDeaths() + inAmount );
    }
}


bool ScoreBoardManager::Write( OutputMemoryBitStream& inOutputStream ) const
{
	int entryCount = mEntries.size();
	
	//we don't know our player names, so it's hard to check for remaining space in the packet...
	//not really a concern now though
	inOutputStream.Write( entryCount );
	for( const Entry& entry: mEntries )
	{
		entry.Write( inOutputStream );
	}
	
	return true;
}



bool ScoreBoardManager::Read( InputMemoryBitStream& inInputStream )
{
	int entryCount;
	inInputStream.Read( entryCount );
	//just replace everything that's here, it don't matter...
	mEntries.resize( entryCount );
	for( Entry& entry: mEntries )
	{
		entry.Read( inInputStream );
	}

	return true;
}


bool ScoreBoardManager::Entry::Write( OutputMemoryBitStream& inOutputStream ) const
{
	bool didSucceed = true;

	inOutputStream.Write( mColor );
	inOutputStream.Write( mPlayerId );
	inOutputStream.Write( mPlayerName );
	inOutputStream.Write( mScore );
    inOutputStream.Write( mKills );
    inOutputStream.Write( mDeaths );

	return didSucceed;
}

bool ScoreBoardManager::Entry::Read( InputMemoryBitStream& inInputStream )
{
	bool didSucceed = true;

	inInputStream.Read( mColor );
	inInputStream.Read( mPlayerId );

	inInputStream.Read( mPlayerName );

	int score;
	inInputStream.Read( score );
	if( didSucceed )
	{
		SetStats( score,  GetPlayerKills(), GetPlayerDeaths());
	}
    
    int kill;
    inInputStream.Read( kill );
    if( didSucceed )
    {
        SetStats( GetScore(), kill, GetPlayerDeaths());
    }
    
    int death;
    inInputStream.Read( death );
    if( didSucceed )
    {
        SetStats( GetScore(),  GetPlayerKills(), death);
    }


	return didSucceed;
}



