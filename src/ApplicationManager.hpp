#ifndef SNN_APPLICATIONMANAGER
#define SNN_APPLICATIONMANAGER

#include <NLib/Base/nNonCopyable.hpp>
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"

class ApplicationManager
	: NLib::NNonCopyable
{
	enum ApplicationState
	{
		APPLICATION_STOP,
		CHOICE_MENU,
		USER_CONTROLLED_SIMULATION,
		SNN_CONTROLLED_SIMULATION,
		SNN_LEARNING
	};

public:
	ApplicationManager();

	void run();

private:
	void initSprites();
	void initPlots();

	void handleKeys();
	void fixedStepUpdate();

	// States setters
	void setApplicationStopState();
	void setChoiceMenuState();
	void setUserControlledSimulationState();


private:
	Framework::Framework	m_framework;
	const float				m_fWorldScale;
	ApplicationState		m_applicationState;


	Framework::SpriteAPtr	m_carSprite;
	Framework::SpriteAPtr	m_backgroundSprite;

	std::string				m_currentTrackPath;

	Simulation::World		m_testWorld;
};

#endif // SNN_APPLICATIONMANAGER