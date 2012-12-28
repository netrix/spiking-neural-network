#include "NeuralNetworkController.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
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

	const float NETWORK_PENALTY = 10000.0f;

	const NSize_t POPULATION_SIZE = 10;//0;//0;
}

NeuralNetworkController::NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network)
	: m_framework(framework)
	, m_world(world)
	, m_testNetwork(network)
	, m_learningNetwork(network.getOutputCount(), network.getInputCount(), network.getStep())
	, m_bStarted(false)
	, m_bInitializated(false)
	, m_bLoopEvaluation(false)
	, m_uCurrentGeneration(0)
	, m_uCurrentReset(0)
{
	m_differentialEvolution.setIndividualSize(network.getParametersCount());
	m_differentialEvolution.setPopulationSize(POPULATION_SIZE);
}

void NeuralNetworkController::initController()
{
	m_framework.setWindowTitle("Neural network controlled simulation");
	
	std::cout << std::endl
		<< "Neural network controlled simulation:" << std::endl
		<< " [ ESC ] - return to choice menu" << std::endl
		<< " [ s ] - start/stop simulation" << std::endl
		<< " [ n ] - evaluate next generation" << std::endl
		<< " [ l ] - loop learning" << std::endl
		<< " [ r ] - reset simulation" << std::endl
		<< std::endl;

	m_world.reset();

	// First time initialization
	if(!m_bInitializated)
	{
		initializeFirstGeneration();
		m_bInitializated = true;
	}
}

void NeuralNetworkController::initializeFirstGeneration()
{
	m_differentialEvolution.randomizeCurrentGeneration();

	std::cout << std::endl << "Initalizating first generation... ";

	for(NSize_t i = 0; i < m_differentialEvolution.getPopulationSize(); ++i)
	{
		float fCost = evaluateIndividual(m_differentialEvolution.getCurrentIndividualData(i));
		m_differentialEvolution.setCost(i, fCost);
	}

	std::cout << "OK, Best score: " << m_differentialEvolution.getBestCost() 
		<< " of individual: " << m_differentialEvolution.getBestIndividualIndex() << std::endl;

	setBestIndividual();
}

void NeuralNetworkController::setBestIndividual()
{
	m_testNetwork.setParameters(m_differentialEvolution.getBestIndividual());
	m_world.reset();

	std::cout << "Best score 2nd: " << evaluateIndividual(m_differentialEvolution.getBestIndividual()) << std::endl;
}

bool NeuralNetworkController::handleKeys()
{
	bool bReturn = false;

	static bool sbL = false;
	static bool sbN = false;
	static bool sbS = false;
	static bool sbR = false;

	if(!sbL && m_framework.checkKeyDown(SDLK_l))
	{
		m_bLoopEvaluation = !m_bLoopEvaluation;
	}
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
		m_testNetwork.reset();
		m_world.reset();
		m_bStarted = false;
	}

	sbL = m_framework.checkKeyDown(SDLK_l);
	sbN = m_framework.checkKeyDown(SDLK_n);
	sbS = m_framework.checkKeyDown(SDLK_s);
	sbR = m_framework.checkKeyDown(SDLK_r);

	if(m_bLoopEvaluation)
	{
		if(m_uCurrentGeneration > 50)
		{
			std::ostringstream oss;
			oss << "../../generations/generation_" << m_uCurrentReset << "_" << m_uCurrentGeneration;
			// Save to file
			saveBestGenerationToFile(oss.str());

			// Reset
			initializeFirstGeneration();

			m_uCurrentGeneration = 0;
			m_uCurrentReset++;
			m_bStarted = true;
		}
		else if(!m_bStarted)
		{
			std::cout << std::endl << "Evaluating generation: " << m_uCurrentGeneration << ", after reset: " << m_uCurrentReset;
			evaluateNextGeneration();
			m_uCurrentGeneration++;
			m_bStarted = true;
		}
	}

	return bReturn;
}

void NeuralNetworkController::fixedStepUpdate()
{
	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	std::cout << "\r"
		<< "Time: " << std::setw(6) << std::setprecision(4) << pe.getTime()
		<< ", Points: " << std::fixed << std::setprecision(4) << pe.getPoints() + NETWORK_PENALTY * m_testNetwork.evaluateParameters();

	if(m_bStarted)
	{
		if(m_testNetwork.checkOutputImpulse(FORWARD)) m_world.moveForward();
		if(m_testNetwork.checkOutputImpulse(BACKWARD)) m_world.moveBackward();
		if(m_testNetwork.checkOutputImpulse(LEFT)) m_world.turnLeft();
		if(m_testNetwork.checkOutputImpulse(RIGHT)) m_world.turnRight();

		m_testNetwork.update();
		m_world.update();

		if(!pe.isRunning() || pe.getTime() > MAX_SIMULATION_TIME)
		{
			m_bStarted = false;
		}
	}
}

float NeuralNetworkController::evaluateIndividual(const SNN::real* pIndividual)
{
	m_learningNetwork.setParameters(pIndividual);
	m_world.reset();

	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	while(pe.isRunning() && pe.getTime() <= MAX_SIMULATION_TIME)
	{
		if(m_learningNetwork.checkOutputImpulse(FORWARD)) m_world.moveForward();
		if(m_learningNetwork.checkOutputImpulse(BACKWARD)) m_world.moveBackward();
		if(m_learningNetwork.checkOutputImpulse(LEFT)) m_world.turnLeft();
		if(m_learningNetwork.checkOutputImpulse(RIGHT)) m_world.turnRight();

		m_learningNetwork.update();
		m_world.update();
	}

	return pe.getPoints() + m_learningNetwork.evaluateParameters() * NETWORK_PENALTY;
}

void NeuralNetworkController::evaluateNextGeneration()
{
	m_differentialEvolution.prepareNextGeneration();

	std::cout << std::endl << "Evaluating next generation... ";

	for(NSize_t i = 0; i < m_differentialEvolution.getPopulationSize(); ++i)
	{
		float fCost = evaluateIndividual(m_differentialEvolution.getNextIndividualData(i));
		m_differentialEvolution.updateIndividual(i, fCost);
	}

	std::cout << "OK, Best score: " << m_differentialEvolution.getBestCost() 
		<< " of individual: " << m_differentialEvolution.getBestIndividualIndex() << std::endl;

	setBestIndividual();
}

void NeuralNetworkController::saveBestGenerationToFile(const std::string& filepath)
{
	// full of hacks, move it to DE class
	std::ofstream out(filepath);

	NSize_t uValueCount = m_differentialEvolution.getIndividualSize() * m_differentialEvolution.getPopulationSize();
	SNN::real* pGeneration = m_differentialEvolution.getCurrentIndividualData(0);
	for(NSize_t i = 0; i < uValueCount; ++i)
	{
		out << pGeneration[i] << std::endl;
	}
}