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
	void evaluateIndividual(SNN::real* pIndividual);

	void evaluateNextGeneration();

	void saveBestGenerationToFile(const std::string& filepath);

private:
	Framework::Framework& m_framework;
	Simulation::World& m_world;
	SNN::SpikingNetwork& m_network;
	DE::DifferentialEvolution m_differentialEvolution;

	bool m_bStarted;
	bool m_bInitializated;

	bool m_bLoopEvaluation;
	NLib::NSize_t m_uCurrentGeneration;
	NLib::NSize_t m_uCurrentReset;
};

#endif // SNN_NEURALNETWORKCONTROLLER