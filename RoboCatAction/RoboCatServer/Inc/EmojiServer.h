class EmojiServer : public Emoji
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new EmojiServer() ); }

	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
	void HandleDying() override;

	virtual void Update() override;

protected:
	EmojiServer();

private:
	float mTimeToDie;
};
