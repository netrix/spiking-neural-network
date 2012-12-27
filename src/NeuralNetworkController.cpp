#include "NeuralNetworkController.hpp"
#include <iostream>
#include <iomanip>

namespace
{
	enum NetworkOutputMap
	{
		FORWARD = 0,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float MAX_SIMULATION_TIME = 5.0f;	// for SIMPLE track
}

NeuralNetworkController::NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network)
	: m_framework(framework)
	, m_world(world)
	, m_network(network)
	, m_bStarted(false)
{
}

void NeuralNetworkController::initController()
{
	m_framework.setWindowTitle("Neural network controlled simulation");
	
	std::cout << "Neural network controlled simulation:" << std::endl
		<< " [ ESC ] - return to choice menu" << std::endl
		<< " [ s ] - start/stop simulation" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;

	m_world.resetCar();
}

bool NeuralNetworkController::handleKeys()
{
	bool bReturn = false;

	static bool sbS = false;
	static bool sbR = false;


	if(!sbS && m_framework.checkKeyDown(SDLK_s))
	{
		m_bStarted = !m_bStarted;
	}
	if(!sbR && m_framework.checkKeyDown(SDLK_r))
	{
		m_world.resetCar();
	}

	sbS = m_framework.checkKeyDown(SDLK_s);
	sbR = m_framework.checkKeyDown(SDLK_r);

	return bReturn;
}

void NeuralNetworkController::fixedStepUpdate()
{
	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	std::cout << "\r"
		<< "Time: " << std::setw(6) << std::setprecision(4) << pe.getTime()
		<< ", Points: " << std::fixed << std::setprecision(4) << pe.getPoints();

	if(m_bStarted)
	{
		if(m_network.checkOutputImpulse(FORWARD)) m_world.moveForward();
		if(m_network.checkOutputImpulse(BACKWARD)) m_world.moveBackward();
		if(m_network.checkOutputImpulse(LEFT)) m_world.turnLeft();
		if(m_network.checkOutputImpulse(RIGHT)) m_world.turnRight();

		m_network.update();
		m_world.update();

		if(pe.getTime() > MAX_SIMULATION_TIME)
		{
			m_bStarted = false;
		}
	}
}
