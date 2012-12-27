#include "SpikingNetwork.hpp"
#include <algorithm>
#include <NLib/Base/nAssert.hpp>

using namespace NLib;

namespace SNN {

SpikingNetwork::SpikingNetwork(NLib::NSize_t uNeuronNum, NLib::NSize_t uInputNum, real fStep)
	: m_fStep(fStep)
{
	NAssert(uNeuronNum > 0, "uNeuronNum must be higher than 0");
	NAssert(uInputNum > 0, "uInputNum must be higher than 0");

	m_spikingNeurons.resize(uNeuronNum);
	
	for(NSize_t i = 0; i < m_spikingNeurons.size(); ++i)
	{
		m_spikingNeurons[i] = new SpikingNeuron(uInputNum, fStep);
	}
}

SpikingNetwork::~SpikingNetwork()
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [](SpikingNeuron* ptr)
	{
		delete ptr;
	});
}

void SpikingNetwork::handleImpulse(NLib::NSize_t uIndex)
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [=](SpikingNeuron* ptr)
	{
		ptr->handleImpulse(uIndex);
	});
}

void SpikingNetwork::update()
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [](SpikingNeuron* ptr)
	{
		ptr->update();
	});
}

NSize_t SpikingNetwork::getParametersCount() const
{
	NSize_t uParameterCount = 0;
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [&uParameterCount](SpikingNeuron* ptr)
	{
		uParameterCount += ptr->getParametersCount();
	});

	return uParameterCount;
}

void SpikingNetwork::getParameters(real* opParameters)
{
	NSize_t uParameterCount = 0;
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [=, &uParameterCount](SpikingNeuron* ptr)
	{
		ptr->getParameters(opParameters + uParameterCount);
		uParameterCount += ptr->getParametersCount();
	});
}

void SpikingNetwork::setParameters(const real* pParameters)
{
	NSize_t uParameterCount = 0;
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [=, &uParameterCount](SpikingNeuron* ptr)
	{
		ptr->setParameters(pParameters + uParameterCount);
		uParameterCount += ptr->getParametersCount();
	});
}

} // SNN