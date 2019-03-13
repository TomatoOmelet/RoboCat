class RoboCatClient : public RoboCat
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new RoboCatClient() ); }

	virtual void Update();
	virtual void	HandleDying() override;
	virtual void	Read( InputMemoryBitStream& inInputStream ) override;
    virtual void GetMoveList() {movements=InputManager::sInstance->GetMoveList();}

protected:
	RoboCatClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;
    MoveList movements;
	
	SpriteComponentPtr	mSpriteComponent;
};
