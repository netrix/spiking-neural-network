#include "SpikingNeuron.hpp"

SpikingNeuron::SpikingNeuron(NLib::NSize_t uInputNum)
	: m_iImpulseTime(0x7fffffff)
	, m_fValue(0.0)
	, mbActive(false)
	, m_fDecayTime(0.0)
	, m_fRelaxation(0.0)
	, m_fThreshold(0.0)
{
	maInputs.create(uInputNum);
}

void SpikingNeuron::handleInput(NLib::NSize_t uInput, real value)
{
	NAssert(uInput < maInputs.size(), "Invalid input index");

	maInputs[uInput].activate();
	mbActive = true;
}

void SpikingNeuron::process()
{
	real m_fValue = 0.0;
	for(int i = 0; i < maInputs.size(); ++i)
	{
		NeuronInput& input = maInputs[i];
		input.m_iImpulseTime += 1;
		m_fValue += input.getImpulseValue();
	}

	// Impulse
	if(m_iImpulseTime > 0 && m_fValue >= m_fThreshold)
	{
		m_iImpulseTime = 0;
	}
	else
	{
		m_iImpulseTime += 1;
		m_fValue += m_fRelaxation * expDrop((real)m_iImpulseTime, m_fDecayTime);
	}
}