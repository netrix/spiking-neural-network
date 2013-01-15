#ifndef SNN_NEURALNETWORKCONTROLLER
#define SNN_NEURALNETWORKCONTROLLER

#include <NLib/Base/nNonCopyable.hpp>
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"
#include "SNN/SpikingNetwork.hpp"
#include "DE/DifferentialEvolution.hpp"
#include "IApplicationController.hpp"

class NeuralNetworkController
	: public IApplicationController
	, NLib::NNonCopyable
{
public:
	NeuralNetworkController(Framework::Framework& framework, Simulation::World& world, SNN::SpikingNetwork& network);

	virtual void initController();
	virtual bool handleKeys();
	virtual void fixedStepUpdate();

private:
	void initializeFirstGeneration();

	float evaluateIndividual(const SNN::real* pIndividual);

	void evaluateGeneration(bool bInit = false);
	void evaluateNextGeneration();

	void setBestIndividual();

	void printStats();

	void evaluateGenerationsFromFiles();
	float loadAndEvaluate(NLib::NSize_t uIndex);

private:
	Framework::Framework&	m_framework;
	Simulation::World&		m_world;
	SNN::SpikingNetwork&	m_testNetwork;

	DE::DifferentialEvolution	m_differentialEvolution;

	bool m_bStarted;
	bool m_bInitializated;

	bool m_bLoopEvaluation;
	NLib::NSize_t m_uCurrentGeneration;
	NLib::NSize_t m_uCurrentReset;
};

#endif // SNN_NEURALNETWORKCONTROLLER