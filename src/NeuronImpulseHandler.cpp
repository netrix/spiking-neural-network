#include "NeuronImpulseHandler.hpp"

NeuronImpulseHandler::NeuronImpulseHandler(SNN::SpikingNetwork& network, NLib::NSize_t uInputIndex)
	: m_network(network)
	, m_uInputIndex(uInputIndex)
{
}

void NeuronImpulseHandler::handleImpulse()
{
	m_network.handleImpulse(m_uInputIndex);
}