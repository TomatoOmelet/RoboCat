//
//  MilkClient.cpp
//  RoboCatActionClient
//
//  Created by Xavier Chua on 2/28/19.
//

#include <RoboCatClientPCH.h>

MilkClient::MilkClient()
{
    mSpriteComponent.reset( new SpriteComponent( this ) );
    mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "milk" ) );
}

