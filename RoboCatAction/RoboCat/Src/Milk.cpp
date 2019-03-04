//
//  Milk.cpp
//  RoboCatAction
//
//  Created by Xavier Chua on 2/28/19.
//

#include <RoboCatPCH.h>

Milk::Milk()
{
    SetScale( GetScale() * 0.5f );
    SetCollisionRadius( 0.25f );
}


bool Milk::HandleCollisionWithCat( RoboCat* inCat )
{
    ( void ) inCat;
    return false;
}



uint32_t Milk::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
{
    uint32_t writtenState = 0;
    
    if( inDirtyState & EMRS_Pose )
    {
        inOutputStream.Write( (bool)true );
        
        Vector3 location = GetLocation();
        inOutputStream.Write( location.mX );
        inOutputStream.Write( location.mY );
        
        inOutputStream.Write( GetRotation() );
        
        writtenState |= EMRS_Pose;
    }
    else
    {
        inOutputStream.Write( (bool)false );
    }
    
    if( inDirtyState & EMRS_Color )
    {
        inOutputStream.Write( (bool)true );
        
        inOutputStream.Write( GetColor() );
        
        writtenState |= EMRS_Color;
    }
    else
    {
        inOutputStream.Write( (bool)false );
    }
    
    
    return writtenState;
}

void Milk::Read( InputMemoryBitStream& inInputStream )
{
    bool stateBit;
    
    inInputStream.Read( stateBit );
    if( stateBit )
    {
        Vector3 location;
        inInputStream.Read( location.mX );
        inInputStream.Read( location.mY );
        SetLocation( location );
        
        float rotation;
        inInputStream.Read( rotation );
        SetRotation( rotation );
    }
    
    
    inInputStream.Read( stateBit );
    if( stateBit )
    {
        Vector3 color;
        inInputStream.Read( color );
        SetColor( color );
    }
}


