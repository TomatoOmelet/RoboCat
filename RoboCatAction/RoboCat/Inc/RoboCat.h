class RoboCat : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'RCAT', GameObject )

	enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health
	};
    float predictedTime;
    float minTime;

	static	GameObject*	StaticCreate()			{ return new RoboCat(); }

	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual	RoboCat*	GetAsCat() override { return this; }

	virtual void Update() override;

	void ProcessInput( float inDeltaTime, const InputState& inInputState );
	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void		SetPlayerId( uint32_t inPlayerId )			{ mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const 	{ return mPlayerId; }

	//void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
	//const Vector3&	GetVelocity()						const	{ return mVelocity; }

	//setter method for robocat
	void			SetPlayerName(string name)					{ mPlayerName = name; }
	//getter method for robocat
	string			GetPlayerName()								{ return mPlayerName; }

	virtual uint32_t	Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;

protected:
	RoboCat();

private:
	string				mPlayerName;

	void	AdjustVelocityByThrust( float inDeltaTime );

	//Vector3				mVelocity;


	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;


	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...
	
	float				mLastMoveTimestamp;

	float				mThrustDir;
	int					mHealth;

	bool				mIsShooting;
	int                 emojiIndex;
    float               mMaxLinearSpeed;

	



};

typedef shared_ptr< RoboCat >	RoboCatPtr;
