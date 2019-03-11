
#include <RoboCatServerPCH.h>



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	sInstance.reset( new Server() );

	return true;
}

Server::Server()
{

	GameObjectRegistry::sInstance->RegisterCreationFunction( 'RCAT', RoboCatServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnServer::StaticCreate );
    GameObjectRegistry::sInstance->RegisterCreationFunction( 'MILK', MilkServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'EMOJ' , EmojiServer::StaticCreate);
    
	InitNetworkManager();
	
	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg( 2 );
	if( !latencyString.empty() )
	{
		latency = stof( latencyString );
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency( latency );
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg( 1 );
	uint16_t port = stoi( portString );

	return NetworkManagerServer::StaticInit( port );
}


namespace
{
	
	void CreateRandomMice( int inMouseCount )
	{
		Vector3 mouseMin( -5.f, -3.f, 0.f );
		Vector3 mouseMax( 5.f, 3.f, 0.f );
		GameObjectPtr go;

		//make a mouse somewhere- where will these come from?
		for( int i = 0; i < inMouseCount; ++i )
		{
			go = GameObjectRegistry::sInstance->CreateGameObject( 'MOUS' );
			Vector3 mouseLocation = RoboMath::GetRandomVector( mouseMin, mouseMax );
			go->SetLocation( mouseLocation );
		}
	}
    
    
    void CreateRandomMilk( int inCount )
    {
        Vector3 milkMin( -5.f, -3.f, 0.f );
        Vector3 milkMax( 5.f, 3.f, 0.f );
        GameObjectPtr go;
        
        //make a mouse somewhere- where will these come from?
        for( int i = 0; i < inCount; ++i )
        {
            go = GameObjectRegistry::sInstance->CreateGameObject( 'MILK' );
            Vector3 mLocation = RoboMath::GetRandomVector( milkMin, milkMax );
            go->SetLocation( mLocation );
        }
    }


}


void Server::SetupWorld()
{
	//spawn some random mice
	CreateRandomMice( 10 );
	
	//spawn more random mice!
	CreateRandomMice( 10 );
    
    CreateRandomMilk(5);
    
    mCurrentTime = Timing::sInstance.GetTimef();
	previousTime = mCurrentTime;
}



void Server::DoFrame()
{
	double current = Timing::sInstance.GetFrameStartTime();

    if(Timing::sInstance.GetFrameStartTime() > mCurrentTime + mMilkSpawnIntervals) {
        mCurrentTime = Timing::sInstance.GetFrameStartTime();
        
        //LOG("Random: %f", );
        CreateRandomMilk(5);
        CreateRandomMice(7);
    }
    
    
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnCats();

	//fixed timestep update
	remainingTime += (current - previousTime);
	previousTime = current;

	while (remainingTime >= TIME_PER_UPDATE)
	{
		Engine::DoFrame();
		remainingTime -= TIME_PER_UPDATE;
	}

	NetworkManagerServer::sInstance->SendOutgoingPackets();

}

void Server::HandleNewClient( ClientProxyPtr inClientProxy )
{
	
	int playerId = inClientProxy->GetPlayerId();
	
	ScoreBoardManager::sInstance->AddEntry( playerId, inClientProxy->GetName() );
	SpawnCatForPlayer( playerId );
}

void Server::SpawnCatForPlayer( int inPlayerId )
{
	RoboCatPtr cat = std::static_pointer_cast< RoboCat >( GameObjectRegistry::sInstance->CreateGameObject( 'RCAT' ) );
	cat->SetColor( ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
	cat->SetPlayerId( inPlayerId );
	cat->SetPlayerName(ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetPlayerName());
	//gotta pick a better spawn location than this...
	cat->SetLocation( Vector3( 1.f - static_cast< float >( inPlayerId ), 0.f, 0.f ) );
}

void Server::HandleLostClient( ClientProxyPtr inClientProxy )
{
	//kill client's cat
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry( playerId );
	RoboCatPtr cat = GetCatForPlayer( playerId );
	if( cat )
	{
		cat->SetDoesWantToDie( true );
	}
}

RoboCatPtr Server::GetCatForPlayer( int inPlayerId )
{
	//run through the objects till we find the cat...
	//it would be nice if we kept a pointer to the cat on the clientproxy
	//but then we'd have to clean it up when the cat died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for( int i = 0, c = gameObjects.size(); i < c; ++i )
	{
		GameObjectPtr go = gameObjects[ i ];
		RoboCat* cat = go->GetAsCat();
		if( cat && cat->GetPlayerId() == inPlayerId )
		{
			return std::static_pointer_cast< RoboCat >( go );
		}
	}

	return nullptr;

}
