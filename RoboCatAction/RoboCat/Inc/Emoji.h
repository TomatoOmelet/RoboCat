class Emoji : public GameObject
{
public:

	CLASS_IDENTIFICATION('EMOJ', GameObject)

		enum EEmojiReplicationState
	{
		EERS_Pose = 1 << 0,
		EERS_Texture = 1 << 1,
		EERS_PlayerId = 1 << 2,

		EERS_AllState = EERS_Pose | EERS_Texture | EERS_PlayerId
	};

	static	GameObject*	StaticCreate() { return new Emoji(); }

	virtual uint32_t	GetAllStateMask()	const override { return EERS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	void		SetPlayerId(int inPlayerId) { mPlayerId = inPlayerId; }
	int			GetPlayerId() const { return mPlayerId; }

	void		InitFromShooter(RoboCat* inShooter);

	virtual void Update() override;

	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;
	
	Vector3 yDiff = Vector3(0, -1, 0);

protected:
	Emoji();

	float		mMuzzleSpeed;
	int			mPlayerId;
	
};

typedef shared_ptr< Emoji >	EmojiPtr;