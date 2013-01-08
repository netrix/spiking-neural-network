#include "SpikingNetwork.hpp"
#include <algorithm>
#include <NLib/Base/nAssert.hpp>
#include <fstream>

using namespace NLib;

namespace SNN {

SpikingNetwork::SpikingNetwork(NLib::NSize_t uNeuronNum, NLib::NSize_t uInputNum, real fStep)
	: m_fStep(fStep)
	, m_uInputCount(uInputNum)
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

bool SpikingNetwork::checkOutputImpulse(NLib::NSize_t uIndex) const
{
	return m_spikingNeurons[uIndex]->isImpulse();
}

void SpikingNetwork::update()
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [](SpikingNeuron* ptr)
	{
		ptr->update();
	});
}

void SpikingNetwork::reset()
{
	std::for_each(m_spikingNeurons.begin(), m_spikingNeurons.end(), [](SpikingNeuron* ptr)
	{
		ptr->reset();
	});
}

NLib::NSize_t SpikingNetwork::getInputCount() const
{
	return m_uInputCount;
}

NLib::NSize_t SpikingNetwork::getOutputCount() const
{
	return m_spikingNeurons.size();
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

void SpikingNetwork::getParameters(real* opParameters) const
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

float SpikingNetwork::evaluateParameters() const
{
	float fValue = 0.0f;
	for(NLib::NSize_t i = 0; i < m_spikingNeurons.size(); ++i)
	{
		fValue += m_spikingNeurons[i]->evaluateParameters();
	}

	return fValue;
}

void SpikingNetwork::saveToFile(const std::string& filepath) const
{
	// Getting data
	std::vector<real> data(getParametersCount());
	getParameters(&data[0]);

	// Writing to file
	std::ofstream fout(filepath);

	for(NSize_t i = 0; i < data.size(); ++i)
	{
		fout << data[i] << std::endl;
	}
}

void SpikingNetwork::loadFromFile(const std::string& filepath)
{
	std::vector<real> data(getParametersCount());

	// Writing to file
	std::ifstream fin(filepath);

	for(NSize_t i = 0; i < data.size(); ++i)
	{
		fin >> data[i];
	}
	
	// Setting data
	setParameters(&data[0]);
}

} // SNN