class MouseServer : public Mouse
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new MouseServer() ); }
	void HandleDying() override;
	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;
	virtual void Update() override;
	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	MouseServer();
};