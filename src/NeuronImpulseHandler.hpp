#ifndef SNN_NEURONIMPULSEHANDLER
#define SNN_NEURONIMPULSEHANDLER

#include "Simulation/Probes/IImpulseHandler.hpp"
#include "SNN/SpikingNetwork.hpp"

class NeuronImpulseHandler
	: public Simulation::Probes::IImpulseHandler
	, NLib::NNonCopyable
{
public:
	NeuronImpulseHandler(SNN::SpikingNetwork& network, NLib::NSize_t uInputIndex);

	virtual void handleImpulse();

private:
	SNN::SpikingNetwork&	m_network;
	NLib::NSize_t			m_uInputIndex;
};

typedef std::auto_ptr<NeuronImpulseHandler> NeuronImpulseHandlerAPtr;

#endif