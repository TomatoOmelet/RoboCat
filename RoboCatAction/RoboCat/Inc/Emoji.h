class Emoji : public GameObject
{
public:

	CLASS_IDENTIFICATION('EMOJI', GameObject)

		enum EEmojiReplicationState
	{
		EERS_Pose = 1 << 0,
		EERS_Texture = 1 << 1,
		EERS_PlayerId = 1 << 2,

		EERS_AllState = EERS_Pose | EERS_Texture | EERS_PlayerId
	};

	static	GameObject*	StaticCreate() { return new Emoji(); }

	virtual uint32_t	GetAllStateMask()	const override { return EYRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3&	GetVelocity() const { return mVelocity; }

	void		SetPlayerId(int inPlayerId) { mPlayerId = inPlayerId; }
	int			GetPlayerId() const { return mPlayerId; }

	void		InitFromShooter(RoboCat* inShooter);

	virtual void Update() override;

	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	Emoji();


	Vector3		mVelocity;

	float		mMuzzleSpeed;
	int			mPlayerId;

};

typedef shared_ptr< Emoji >	EmojiPtr;