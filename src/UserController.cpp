#include "UserController.hpp"
#include <iostream>
#include <iomanip>

UserController::UserController(Framework::Framework& framework, Simulation::World& world)
	: m_framework(framework)
	, m_world(world)
{
}

void UserController::initController()
{
	m_framework.setWindowTitle("User controlled simulation");
	
	std::cout << std::endl
		<< "User controlled simulation:" << std::endl
		<< " [ ESC ] - return to choice menu" << std::endl
		<< " [ UP ] - move forward" << std::endl
		<< " [ DOWN ] - move backward" << std::endl
		<< " [ LEFT ] - turn left" << std::endl
		<< " [ RIGHT ] - turn right" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;

	m_world.resetCar();
}

bool UserController::handleKeys()
{
	bool bReturn = false;

	static bool sbR = false;

	if(!sbR && m_framework.checkKeyDown(SDLK_r))
	{
		m_world.resetCar();
	}

	sbR = m_framework.checkKeyDown(SDLK_r);

	return bReturn;
}

void UserController::fixedStepUpdate()
{
	if(m_framework.checkKeyDown(SDLK_UP)) m_world.moveForward();
	if(m_framework.checkKeyDown(SDLK_DOWN)) m_world.moveBackward();
	if(m_framework.checkKeyDown(SDLK_LEFT)) m_world.turnLeft();
	if(m_framework.checkKeyDown(SDLK_RIGHT)) m_world.turnRight();

	m_world.update();

	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	std::cout << "\r"
		<< "Time: " << std::setw(6) << std::setprecision(4) << pe.getTime()
		<< ", Points: " << std::setprecision(4) << pe.getPoints();
}
