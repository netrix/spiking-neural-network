#ifndef SNN_APPLICATIONMANAGER
#define SNN_APPLICATIONMANAGER

#include <NLib/Base/nNonCopyable.hpp>
#include "Plots/ImpulsePlotBundle.hpp"
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"

#include "IApplicationController.hpp"
#include "UserController.hpp"

class ApplicationManager
	: public IApplicationController
	, NLib::NNonCopyable
{
public:
	ApplicationManager();

	void run();

private:
	void initSprites();
	void initPlots();
	void initWorld();

	void draw();
	bool handleApplicationKeys();

	virtual void initController();
	virtual bool handleKeys();
	virtual void fixedStepUpdate();

	void setApplicationController(IApplicationController& pController);

private:
	Framework::Framework		m_framework;
	const float					m_fWorldScale;
	IApplicationController*		m_pApplicationController;

	Framework::SpriteAPtr		m_carSprite;
	Framework::SpriteAPtr		m_backgroundSprite;

	bool						m_bShowPlots;
	std::string					m_currentTrackPath;

	Plots::ImpulsePlotBundle	m_impulsePlotBundle;
	Simulation::World			m_testWorld;

	UserController				m_userController;
};

#endif // SNN_APPLICATIONMANAGER