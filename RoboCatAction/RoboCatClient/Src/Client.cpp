
#include <RoboCatClientPCH.h>

bool Client::StaticInit( )
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();

	if( WindowManager::StaticInit() == false )
	{
        return false;
	}

    if( GraphicsDriver::StaticInit( WindowManager::sInstance->GetMainWindow() ) == false )
	{
        return false;
    }

	TextureManager::StaticInit();
	RenderManager::StaticInit();
	InputManager::StaticInit();

	HUD::StaticInit();

	sInstance.reset( client );

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'RCAT', RoboCatClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnClient::StaticCreate );
    GameObjectRegistry::sInstance->RegisterCreationFunction( 'MILK', MilkClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'EMOJ', EmojiClient::StaticCreate);

	string destination = StringUtils::GetCommandLineArg( 1 );
	string name = StringUtils::GetCommandLineArg( 2 );

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString( destination );

	NetworkManagerClient::StaticInit( *serverAddress, name );

	NetworkManagerClient::sInstance->SetSimulatedLatency( 0.0f );
	previousTime = Timing::sInstance.GetTimef();
}



void Client::DoFrame()
{
	double current = Timing::sInstance.GetFrameStartTime();

	InputManager::sInstance->Update();

	//fixed timestep update
	remainingTime += (current - previousTime);
	previousTime = current;

	while (remainingTime >= TIME_PER_UPDATE)
	{
		Engine::DoFrame();
		remainingTime -= TIME_PER_UPDATE;
	}

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	float percent = remainingTime / TIME_PER_UPDATE;
	RenderManager::sInstance->RenderTheFuture(percent);

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent( SDL_Event* inEvent )
{
	switch( inEvent->type )
	{
	case SDL_KEYDOWN:
		InputManager::sInstance->HandleInput( EIA_Pressed, inEvent->key.keysym.sym );
		break;
	case SDL_KEYUP:
		InputManager::sInstance->HandleInput( EIA_Released, inEvent->key.keysym.sym );
		break;
	default:
		break;
	}
}

