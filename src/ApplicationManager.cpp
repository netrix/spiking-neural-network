#include "ApplicationManager.hpp"
#include <iostream>

using namespace NLib::Math;

namespace {

// Framework settings
Framework::FrameworkSettings FRAMEWORK_SETTINGS = { 800, 600, 32 };

// World settings
const float STEP = 1.0f / 60.0f;
const float WORLD_SCALE = 0.2f;

// Sprites
const std::string CAR_SPRITE_IMAGE_PATH = "../../data/car.png";
const std::string BACKGROUND_SPRITE_IMAGE_PATH = "../../data/background.png";

// Trakcs
const std::string SIMPLE_TRACK_PATH = "../../data/simple_track.txt";
const std::string COMPLEX_TRACK_PATH = "../../data/complex_track.txt";

}

ApplicationManager::ApplicationManager()
	: m_framework(FRAMEWORK_SETTINGS, WORLD_SCALE)
	, m_fWorldScale(WORLD_SCALE)
	, m_pApplicationController(null)
	, m_currentTrackPath(SIMPLE_TRACK_PATH)
	, m_testWorld(m_framework, WORLD_SCALE, STEP)
	, m_userController(m_framework, m_testWorld)
{
	m_framework.setDebugDraw(true);
}


void ApplicationManager::initSprites()
{
	// Loading sprites
	m_carSprite = m_framework.createSprite(CAR_SPRITE_IMAGE_PATH);
	m_backgroundSprite = m_framework.createSprite(BACKGROUND_SPRITE_IMAGE_PATH);

	// Prepar car sprite
	NMVector2f offset = -m_carSprite->getSize() * 0.1f;
	m_carSprite->setOffset(offset);
	m_carSprite->setSize(m_carSprite->getSize() * m_fWorldScale);

	// Prepare backgroudn sprite
	NMVector2f backgroundSize = { 800 * m_fWorldScale, 600 * m_fWorldScale };
	m_backgroundSprite->setSize(backgroundSize);
}

void ApplicationManager::initPlots()
{
}

void ApplicationManager::initWorld()
{
	m_currentTrackPath = "../../data/complex_track.txt";
	m_testWorld.loadTrack(m_currentTrackPath);
	m_testWorld.resetCar();
}

bool ApplicationManager::handleApplicationKeys()
{
	// Handling controllers
	bool bReturn = m_pApplicationController->handleKeys();

	static bool sbEscape = false;

	if(!bReturn)
	{
		// Handling common escape
		if(!sbEscape && m_framework.checkKeyDown(SDLK_ESCAPE))
		{
			if(m_pApplicationController == this)
			{
				m_pApplicationController = null;
				return true;
			}
			else
			{
				setApplicationController(*this);
			}
		}
	}
	sbEscape = m_framework.checkKeyDown(SDLK_ESCAPE);

	return bReturn;
}

bool ApplicationManager::handleKeys()
{
	bool bReturn = false;

	static bool sbF1 = false;
	static bool sbF11 = false;
	static bool sbF12 = false;
	
	if(!bReturn && !sbF1 && m_framework.checkKeyDown(SDLK_F1))
	{
		setApplicationController(m_userController);
		bReturn = true;
	}

	// Track
	if(!sbF11 && m_framework.checkKeyDown(SDLK_F11))
	{
		m_currentTrackPath = "../../data/simple_track.txt";
		m_testWorld.loadTrack(m_currentTrackPath);
	}
	if(!sbF12 && m_framework.checkKeyDown(SDLK_F12))
	{
		m_currentTrackPath = "../../data/complex_track.txt";
		m_testWorld.loadTrack(m_currentTrackPath);
	}

	sbF1 = m_framework.checkKeyDown(SDLK_F1);
	sbF11 = m_framework.checkKeyDown(SDLK_F11);
	sbF12 = m_framework.checkKeyDown(SDLK_F12);

	return bReturn;
}

void ApplicationManager::fixedStepUpdate()
{
}

void ApplicationManager::setApplicationController(IApplicationController& pController)
{
	m_pApplicationController = &pController;
	m_pApplicationController->initController();
}

void ApplicationManager::initController()
{
	m_framework.setWindowTitle("ApplicationManager choice menu");
	
	std::cout << "ApplicationManager choice menu:" << std::endl
		<< " [ F1 ] - User controlled simulation" << std::endl
		<< " [ F2 ] - SNN controlled simulation" << std::endl
		<< " [ F3 ] - SNN learning mode" << std::endl
		<< " [ F11 ] - Load simple track" << std::endl
		<< " [ F12 ] - Load complex track" << std::endl
		<< " [ ESC ] - Quit application" << std::endl
		<< std::endl;
}

void ApplicationManager::run()
{
	initSprites();
	initPlots();
	initWorld();

	setApplicationController(*this);

	// Application loop
	float fFixedTimer = 0.0f;
	while(m_pApplicationController != null && m_framework.update())
	{
		// Drawing
		m_testWorld.draw(*m_carSprite, *m_backgroundSprite);

		// Handling application keys
		if(handleApplicationKeys())
		{
			continue;
		}

		// Fixed time loop
		fFixedTimer += m_framework.getTimeDelta();
		if(fFixedTimer > 2.0f)
		{
				fFixedTimer = 0.0f;
		}

		while(fFixedTimer > STEP)
		{
			fFixedTimer -= STEP;

			// Update with fixed step
			m_pApplicationController->fixedStepUpdate();
		}

		m_framework.flipScreen();
	}
}

