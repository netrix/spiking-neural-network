#include "SpikingNetwork.hpp"
#include <algorithm>

namespace SNN {

SpikingNetwork::SpikingNetwork(real fStep)
	: m_fStep(fStep)
{
}

SpikingNetwork::~SpikingNetwork()
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [](SpikingNeuron* ptr)
	{
		delete ptr;
	});
}

void SpikingNetwork::addNeuron(SpikingNeuronAPtr neuron)
{
	m_spikingNeurons.push_back(neuron.release());
}

void SpikingNetwork::handleImpulse(NLib::NSize_t uIndex)
{
}

void SpikingNetwork::update()
{
}

} // SNN