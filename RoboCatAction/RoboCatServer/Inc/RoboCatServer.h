enum ECatControlType
{
	ESCT_Human,
	ESCT_AI
};

class RoboCatServer : public RoboCat
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new RoboCatServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetCatControlType( ECatControlType inCatControlType ) { mCatControlType = inCatControlType; }

	void TakeDamage( int inDamagingPlayerId );
    
    void IncHealth();
    
    void UpdateSpeed(int value);

	void SetEmoji(EmojiPtr emo);

protected:
	RoboCatServer();
	EmojiPtr emoji = nullptr;

private:

	void HandleShooting();
	void HandleEmoji();
    GameObject::movementStates GetPredictedState();
	ECatControlType	mCatControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

	//just in case the get input here is not GetButton(), add some interval
	float		mTimeOfNextEmoji;
	float		mTimeBetweenEmojis;
};
