class EmojiServer : public Emoji
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new EmojiServer() ); }

	virtual bool		HandleCollisionWithCat( RoboCat* inCat ) override;

	virtual void Update() override;

	void SetCat(RoboCatPtr cat) { mCat = cat; }

protected:
	EmojiServer();
	RoboCatPtr mCat;
};

typedef shared_ptr< EmojiServer >	EmojiServerPtr;