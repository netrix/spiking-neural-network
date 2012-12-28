#include "NeuralNetworkController.hpp"
#include <iostream>
#include <iomanip>

using namespace NLib;

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

	const NSize_t POPULATION_SIZE = 100;
}

NeuralNetworkController::NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network)
	: m_framework(framework)
	, m_world(world)
	, m_network(network)
	, m_bStarted(false)
	, m_bInitializated(false)
{
	m_differentialEvolution.setIndividualSize(m_network.getParametersCount());
	m_differentialEvolution.setPopulationSize(POPULATION_SIZE);
	m_differentialEvolution.randomizeCurrentGeneration();
}

void NeuralNetworkController::initController()
{
	m_framework.setWindowTitle("Neural network controlled simulation");
	
	std::cout << std::endl
		<< "Neural network controlled simulation:" << std::endl
		<< " [ ESC ] - return to choice menu" << std::endl
		<< " [ s ] - start/stop simulation" << std::endl
		<< " [ n ] - evaluate next generation" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;

	m_world.resetCar();

	// First time initialization
	if(!m_bInitializated)
	{
		std::cout << std::endl << "Initalizating first generation... ";

		for(NSize_t i = 0; i < m_differentialEvolution.getPopulationSize(); ++i)
		{
			evaluateIndividual(m_differentialEvolution.getCurrentIndividualData(i));
			m_differentialEvolution.setCost(i, m_world.getPassageEvaluator().getPoints());
		}
		m_bInitializated = true;

		std::cout << "OK, Best score: " << m_differentialEvolution.getBestCost() 
			<< " of individual: " << m_differentialEvolution.getBestIndividualIndex() << std::endl;
	}
}

bool NeuralNetworkController::handleKeys()
{
	bool bReturn = false;

	static bool sbN = false;
	static bool sbS = false;
	static bool sbR = false;

	if(!sbN && m_framework.checkKeyDown(SDLK_n))
	{
		evaluateNextGeneration();
	}
	if(!sbS && m_framework.checkKeyDown(SDLK_s))
	{
		m_bStarted = !m_bStarted;
	}
	if(!sbR && m_framework.checkKeyDown(SDLK_r))
	{
		m_world.resetCar();
	}

	sbN = m_framework.checkKeyDown(SDLK_n);
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

void NeuralNetworkController::evaluateIndividual(SNN::real* pIndividual)
{
	m_network.setParameters(pIndividual);
	m_world.resetCar();

	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	while(pe.isRunning() && pe.getTime() <= MAX_SIMULATION_TIME)
	{
		m_network.update();
		m_world.update();
	}
}

void NeuralNetworkController::evaluateNextGeneration()
{
	m_differentialEvolution.prepareNextGeneration();

	std::cout << std::endl << "Evaluating next generation... ";

	for(NSize_t i = 0; i < m_differentialEvolution.getPopulationSize(); ++i)
	{
		evaluateIndividual(m_differentialEvolution.getNextIndividualData(i));
		m_differentialEvolution.updateIndividual(i, m_world.getPassageEvaluator().getPoints());
	}

	std::cout << "OK, Best score: " << m_differentialEvolution.getBestCost() 
		<< " of individual: " << m_differentialEvolution.getBestIndividualIndex() << std::endl;
}