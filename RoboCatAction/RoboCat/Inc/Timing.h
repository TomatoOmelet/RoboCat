class Timing
{
public:

	Timing();
	
	void Update();

	float GetDeltaTime() const { return mDeltaTime; }

	double GetTime() const;

	float GetTimef() const
	{
		return static_cast< float >( GetTime() );
	}

	float GetFrameStartTime() const { return mFrameStartTimef; }

	double GetLastUpdateTime() const { return lastUpdatedTime; }
	void SetLastUpdateTime(double value) { lastUpdatedTime = value; }

	static Timing sInstance; 

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

	double      lastUpdatedTime = 0;
	//double		timePerUpdate = 
};