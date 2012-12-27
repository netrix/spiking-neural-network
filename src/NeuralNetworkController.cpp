#include "NeuralNetworkController.hpp"
#include <iostream>

namespace
{
	enum NetworkOutputMap
	{
		FORWARD = 0,
		BACKWARD,
		LEFT,
		RIGHT
	};
}

NeuralNetworkController::NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network)
	: m_framework(framework)
	, m_world(world)
	, m_network(network)
{
}

void NeuralNetworkController::initController()
{
	m_framework.setWindowTitle("Neural network controlled simulation");
	
	std::cout << "Neural network controlled simulation:" << std::endl
		<< " [ ESC ] - stop simulation" << std::endl
		//<< " [ UP ] - move forward" << std::endl
		//<< " [ DOWN ] - move backward" << std::endl
		//<< " [ LEFT ] - turn left" << std::endl
		//<< " [ RIGHT ] - turn right" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;

	m_world.resetCar();
}

bool NeuralNetworkController::handleKeys()
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

void NeuralNetworkController::fixedStepUpdate()
{
	if(m_network.checkOutputImpulse(FORWARD)) m_world.moveForward();
	if(m_network.checkOutputImpulse(BACKWARD)) m_world.moveBackward();
	if(m_network.checkOutputImpulse(LEFT)) m_world.turnLeft();
	if(m_network.checkOutputImpulse(RIGHT)) m_world.turnRight();

	m_network.update();
	m_world.update();
}
