ICS 167 RoboCats Networked Game Readme

Wayne 
Sean Kim 74239361
Muhammad 
Xavier Chua 89546877


Mechanics Implemented:

Mice Movement
	Mice now move in random directions.

	Files Modified:


Emotes
	Players can press the 1-3 keys in order to display emotes that other players in the game can also see.

	Files Modified:


Milk Game Object
	Implemented a new game object (Milk with the sprite of the new pokemon grookey) that heals the player's robocat (capped at 15) and increases its speed. Also added some code to spawn milk/mice at every 10 second interval.

	Files Modified:
		/Assets/milk.png
		RoboCatServerPCH.h
		RoboCatClientPCH.h
		RoboCatShared.h
		Milk.h/.cpp
		MilkClient.h/.cpp
		MilkServer.h/.cpp
		RoboCat.h
		RoboCatServer
		World.h
		Client.cpp
		Server.cpp
		TextureManager.cpp

Death Log
	Implemented a kill feed at the top of the screen displaying a message when a player kills another player, indicating who killed who. Also implemented helper functions/variables to get names of each robocat.

	Files Modified:
		Added DeathLogManager.h/.cpp
		Modified Engine.cpp
		Modified HUD.h/.cpp
		NetworkManagerClient.h/.cpp
		NetworkManagerServer.h/.cpp
		RoboCatServer.cpp
		RoboCat.h
		RoboCatShared.h
		Yarn.h/.cpp
		Server.cpp

Scoreboard Tweaks
	Modified the scoreboard data to also display kills/deaths of each player.

	Files Modified:
		ScoreBoardManager.h/.cpp
		RoboCatServer.cpp
