#include "NeuralNetworkController.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>

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

	const float MAX_SIMULATION_TIME = 20.0f;	// for SIMPLE track

	const float NETWORK_PENALTY = 1000.0f;
	const float STEER_PENALTY = 1000.0f;

	const NSize_t POPULATION_SIZE = 1000;

	const std::string DEFAULT_GENERATION_FILE = "../../generations/default.txt";
	const std::string DEFAULT_NETWORK_DRIVER_FILE = "../../default_network_driver.txt";
}

NeuralNetworkController::NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network)
	: m_framework(framework)
	, m_world(world)
	, m_testNetwork(network)
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
		<< " [ w ] - write generation to file" << std::endl
		<< " [ o ] - load generation from file" << std::endl
		<< " [ F4 ] - reinitialize generation" << std::endl
		<< " [ F5 ] - save current driver to file" << std::endl
		<< " [ F9 ] - load current driver from file" << std::endl
		<< std::endl;

	m_world.reset();
}

void NeuralNetworkController::initializeFirstGeneration()
{
	m_differentialEvolution.randomizeCurrentGeneration();

	std::cout << std::endl << "Initalizating first generation... ";

	evaluateGeneration(true);
}

void NeuralNetworkController::setBestIndividual()
{
	m_testNetwork.setParameters(m_differentialEvolution.getBestIndividual());
	m_testNetwork.reset();
	m_world.reset();
}

bool NeuralNetworkController::handleKeys()
{
	bool bReturn = false;

	static bool sbE = false;
	static bool sbL = false;
	static bool sbN = false;
	static bool sbO = false;
	static bool sbR = false;
	static bool sbS = false;
	static bool sbW = false;
	static bool sbF4 = false;
	static bool sbF5 = false;
	static bool sbF7 = false;
	static bool sbF8 = false;
	static bool sbF9 = false;

	if(!sbE && m_framework.checkKeyDown(SDLK_e))
	{
		evaluateGeneration();
	}
	if(!sbL && m_framework.checkKeyDown(SDLK_l))
	{
		m_bLoopEvaluation = !m_bLoopEvaluation;
	}
	if(!sbN && m_framework.checkKeyDown(SDLK_n))
	{
		// First time initialization
		if(!m_bInitializated)
		{
			initializeFirstGeneration();
			m_bInitializated = true;
		}
		else
		{
			evaluateNextGeneration();
		}
	}
	if(!sbO && m_framework.checkKeyDown(SDLK_o))
	{
		m_differentialEvolution.loadGenerationFromFile(DEFAULT_GENERATION_FILE);
		evaluateGeneration(true);
		m_bInitializated = true;
	}
	if(!sbR && m_framework.checkKeyDown(SDLK_r))
	{
		m_testNetwork.reset();
		m_world.reset();
		m_bStarted = false;
	}
	if(!sbS && m_framework.checkKeyDown(SDLK_s))
	{
		m_bStarted = !m_bStarted;
	}
	if(!sbW && m_framework.checkKeyDown(SDLK_w))
	{
		m_differentialEvolution.saveGenerationToFile(DEFAULT_GENERATION_FILE);
	}
	if(!sbF4 && m_framework.checkKeyDown(SDLK_F4))
	{
		m_differentialEvolution.randomizeCurrentGeneration();
		evaluateGeneration(true);
	}
	if(!sbF5 && m_framework.checkKeyDown(SDLK_F5))
	{
		m_testNetwork.saveToFile(DEFAULT_NETWORK_DRIVER_FILE);
	}
	if(!sbF7 && m_framework.checkKeyDown(SDLK_F7))
	{
		NLib::NSize_t uGeneration = 10738;

		std::cin >> uGeneration;

		float fCost = loadAndEvaluate(uGeneration);
		std::cout << "Cost of generation: " << uGeneration << " is " << fCost << " of individual " 
				<< m_differentialEvolution.getBestIndividualIndex() << ", average: " 
				<< m_differentialEvolution.getCostStats().x << std::endl;
	}
	if(!sbF8 && m_framework.checkKeyDown(SDLK_F8))
	{
		evaluateGenerationsFromFiles();
	}
	if(!sbF9 && m_framework.checkKeyDown(SDLK_F9))
	{
		m_testNetwork.loadFromFile(DEFAULT_NETWORK_DRIVER_FILE);
	}

	sbE = m_framework.checkKeyDown(SDLK_e);
	sbL = m_framework.checkKeyDown(SDLK_l);
	sbN = m_framework.checkKeyDown(SDLK_n);
	sbO = m_framework.checkKeyDown(SDLK_o);
	sbR = m_framework.checkKeyDown(SDLK_r);
	sbS = m_framework.checkKeyDown(SDLK_s);
	sbW = m_framework.checkKeyDown(SDLK_w);
	sbF4 = m_framework.checkKeyDown(SDLK_F4);
	sbF5 = m_framework.checkKeyDown(SDLK_F5);
	sbF7 = m_framework.checkKeyDown(SDLK_F7);
	sbF8 = m_framework.checkKeyDown(SDLK_F8);
	sbF9 = m_framework.checkKeyDown(SDLK_F9);

	if(m_bLoopEvaluation)
	{
		// First time initialization
		if(!m_bInitializated)
		{
			initializeFirstGeneration();
			m_bInitializated = true;
		}

		//if(m_uCurrentGeneration > 1500000000)
		//{
		//	std::ostringstream oss;
		//	oss << "../../generations/generation_" << m_uCurrentReset << "_" << m_uCurrentGeneration;
		//	// Save to file
		//	m_differentialEvolution.saveGenerationToFile(oss.str());

		//	// Reset
		//	initializeFirstGeneration();

		//	m_uCurrentGeneration = 0;
		//	m_uCurrentReset++;
		//	m_bStarted = true;
		//}
		//else 
		if(!m_bStarted)
		{
			std::cout << std::endl << "Evaluating generation: " << m_uCurrentGeneration << ", after reset: " << m_uCurrentReset;
			evaluateNextGeneration();

			// Save to file
			std::ostringstream oss;
			oss << "../../generations/generation_" << m_uCurrentReset << "_" << m_uCurrentGeneration;
			m_differentialEvolution.saveGenerationToFile(oss.str());

			m_uCurrentGeneration++;
			m_bStarted = true;
		}
	}

	return bReturn;
}

void NeuralNetworkController::fixedStepUpdate()
{
	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	float fSteerEvaluation = m_testNetwork.checkOutputImpulse(FORWARD)
		&& m_testNetwork.checkOutputImpulse(BACKWARD) ? STEER_PENALTY : 0.0f;

	fSteerEvaluation += m_testNetwork.checkOutputImpulse(LEFT) 
		&& m_testNetwork.checkOutputImpulse(RIGHT) ? STEER_PENALTY : 0.0f;

	std::cout << "\r" 
		<< "Time: " << std::setw(6) << std::setprecision(4) << pe.getTime()
		<< ", Points: " << std::setprecision(4) << pe.getPoints() + fSteerEvaluation + m_testNetwork.evaluateParameters() * NETWORK_PENALTY
		<< ", Forward output value: " << std::scientific << m_testNetwork.getNeuron(FORWARD).getValue() << std::fixed;

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
	m_testNetwork.setParameters(pIndividual);
	m_testNetwork.reset();
	m_world.reset();

	const Simulation::PassageEvaluator& pe = m_world.getPassageEvaluator();

	float fSteerEvaluation = 0.0f; //STEER_PENALTY

	while(pe.isRunning() && pe.getTime() <= MAX_SIMULATION_TIME)
	{
		if(m_testNetwork.checkOutputImpulse(FORWARD)) m_world.moveForward();
		if(m_testNetwork.checkOutputImpulse(BACKWARD)) m_world.moveBackward();
		if(m_testNetwork.checkOutputImpulse(LEFT)) m_world.turnLeft();
		if(m_testNetwork.checkOutputImpulse(RIGHT)) m_world.turnRight();

		fSteerEvaluation += m_testNetwork.checkOutputImpulse(FORWARD) 
						&& m_testNetwork.checkOutputImpulse(BACKWARD) ? STEER_PENALTY : 0.0f;

		fSteerEvaluation += m_testNetwork.checkOutputImpulse(LEFT) 
						&& m_testNetwork.checkOutputImpulse(RIGHT) ? STEER_PENALTY : 0.0f;

		m_testNetwork.update();
		m_world.update();
	}

	return pe.getPoints() + fSteerEvaluation + m_testNetwork.evaluateParameters() * NETWORK_PENALTY;	// TODO: Not sure if evaluation of network parameter is needed
}

void NeuralNetworkController::evaluateNextGeneration()
{
	m_differentialEvolution.prepareNextGeneration();

	std::cout << std::endl << "Evaluating next generation... ";

	evaluateGeneration();
}

void NeuralNetworkController::evaluateGeneration(bool bInit)
{
	std::cout << std::endl;

	for(NSize_t i = 0; i < m_differentialEvolution.getPopulationSize(); ++i)
	{
		std::cout << "Evaluating generation... " << i << "/" << m_differentialEvolution.getPopulationSize() << "\r";

		// Double check
		float fCost = 0.0f;
		
		if(bInit)
		{
			fCost = evaluateIndividual(m_differentialEvolution.getCurrentIndividualData(i));
			m_differentialEvolution.setCost(i, fCost);
		}
		else
		{
			fCost = evaluateIndividual(m_differentialEvolution.getNextIndividualData(i));
			m_differentialEvolution.updateIndividual(i, fCost);
		}
	}

	printStats();
	setBestIndividual();
}

void NeuralNetworkController::printStats()
{
	Math::NMVector2f generationStats = m_differentialEvolution.getCostStats();

	std::cout << std::endl
		<< "Best score: " << m_differentialEvolution.getBestCost() 
		<< " of individual: " << m_differentialEvolution.getBestIndividualIndex()
		<< ". Generation average: " << generationStats.x << ", std: " 
		<< generationStats.y << std::endl;
}

void NeuralNetworkController::evaluateGenerationsFromFiles()
{
		std::ofstream results("generations_best_results.txt");
		NLib::NSize_t MAX_GENERATION = 10738;

		struct T
		{
			NLib::NSize_t a, b;
			float fCostA, fCostB;
		};
		std::queue<T> indices;

		T actual = { 0, MAX_GENERATION };
		actual.fCostA = loadAndEvaluate(0);
		std::cout << "Cost of generation: " << 0 << " is " << actual.fCostA << std::endl;
		results << "Cost of generation: " << 0 << " is " << actual.fCostA << " of individual " << m_differentialEvolution.getBestIndividualIndex() << ", average: " << m_differentialEvolution.getCostStats().x << std::endl;

		actual.fCostB = loadAndEvaluate(MAX_GENERATION);
		std::cout << "Cost of generation: " << MAX_GENERATION << " is " << actual.fCostB << std::endl;
		results << "Cost of generation: " << MAX_GENERATION << " is " << actual.fCostB << " of individual " << m_differentialEvolution.getBestIndividualIndex() << ", average: " << m_differentialEvolution.getCostStats().x << std::endl;

		if(actual.fCostA != actual.fCostB)
		{
			indices.push(actual);
		}

		while(!indices.empty())
		{
			actual = indices.front();
			indices.pop();

			if(actual.b > actual.a + 1)
			{
				NLib::NSize_t uNewIndex = ((actual.b - actual.a) >> 1) + actual.a;
				float fNewCost = loadAndEvaluate(uNewIndex);

				std::cout << "Cost of generation: " << uNewIndex << " is " << fNewCost << std::endl;
				results << "Cost of generation: " << uNewIndex << " is " << fNewCost << " of individual " << m_differentialEvolution.getBestIndividualIndex() << ", average: " << m_differentialEvolution.getCostStats().x << std::endl;
				results.flush();

				if(actual.fCostA != fNewCost)
				{
					T n = { actual.a, uNewIndex, actual.fCostA, fNewCost };
					indices.push(n);
				}
				if(actual.fCostB != fNewCost)
				{
					T n = { uNewIndex, actual.b, fNewCost, actual.fCostB };
					indices.push(n);
				}
			}
		}
}

float NeuralNetworkController::loadAndEvaluate(NLib::NSize_t uIndex)
{
	std::ostringstream sout;
	sout << "../../generations/generation_0_" << uIndex;

	m_differentialEvolution.loadGenerationFromFile(sout.str());
	evaluateGeneration(true);

	return m_differentialEvolution.getBestCost();
}