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
	, m_applicationState(APPLICATION_STOP)
	, m_currentTrackPath(SIMPLE_TRACK_PATH)
	, m_testWorld(m_framework, WORLD_SCALE, STEP)
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

void ApplicationManager::handleKeys()
{
	static bool sbEscape = false;
	static bool sbF1 = false;

	if(!sbEscape && m_framework.checkKeyDown(SDLK_ESCAPE))
	{
		if(m_applicationState == CHOICE_MENU)
		{
			setApplicationStopState();
		}
		else
		{
			setChoiceMenuState();
		}
	}
	if(!sbF1 && m_framework.checkKeyDown(SDLK_F1))
	{
		setUserControlledSimulationState();
	}

	sbEscape = m_framework.checkKeyDown(SDLK_ESCAPE);
	sbF1 = m_framework.checkKeyDown(SDLK_F1);
}

void ApplicationManager::fixedStepUpdate()
{
}

void ApplicationManager::setApplicationStopState()
{
	m_applicationState = APPLICATION_STOP;
}

void ApplicationManager::setChoiceMenuState()
{
	m_applicationState = CHOICE_MENU;

	m_framework.setWindowTitle("ApplicationManager choice menu");
	
	std::cout << "ApplicationManager choice menu:" << std::endl
		<< " [ F1 ] - User controlled simulation" << std::endl
		<< " [ F2 ] - SNN controlled simulation" << std::endl
		<< " [ F3 ] - SNN learning mode" << std::endl
		<< std::endl;
}

void ApplicationManager::setUserControlledSimulationState()
{
	m_applicationState = USER_CONTROLLED_SIMULATION;

	m_framework.setWindowTitle("User controlled simulation");
	
	std::cout << "User controlled simulation:" << std::endl
		<< " [ ESC ] - stop simulation" << std::endl
		<< " [ UP ] - move forward" << std::endl
		<< " [ DOWN ] - move backward" << std::endl
		<< " [ LEFT ] - turn left" << std::endl
		<< " [ RIGHT ] - turn right" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;
}

void ApplicationManager::run()
{
	initSprites();
	initPlots();

	setChoiceMenuState();

	// Application loop
	float fFixedTimer = 0.0f;
	while(m_applicationState != APPLICATION_STOP && m_framework.update())
	{
		// Drawing
		m_testWorld.draw(*m_carSprite, *m_backgroundSprite);

		// Handling application keys
		handleKeys();

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
			fixedStepUpdate();
		}

		m_framework.flipScreen();
	}
}

