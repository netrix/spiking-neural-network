#ifndef SNN_NEURALNETWORKCONTROLLER
#define SNN_NEURALNETWORKCONTROLLER

#include <NLib/Base/nNonCopyable.hpp>
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"
#include "SNN/SpikingNetwork.hpp"
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
	Framework::Framework& m_framework;
	Simulation::World& m_world;
	SNN::SpikingNetwork& m_network;

	bool m_bStarted;
};

#endif // SNN_NEURALNETWORKCONTROLLER