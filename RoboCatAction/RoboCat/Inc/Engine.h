#include <SDL_events.h>

class Engine
{
public:

	virtual ~Engine();
	static std::unique_ptr< Engine >	sInstance;

	virtual int		Run();
	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
	virtual void	HandleEvent( SDL_Event* inEvent );

protected:

	Engine();

	virtual void	DoFrame();

	double previousTime;
	double remainingTime = 0;
	double const TIME_PER_UPDATE = 0.016;

private:


			
			int		DoRunLoop();

			bool	mShouldKeepRunning;

			

};