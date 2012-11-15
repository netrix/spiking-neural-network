#include "NeuronInput.hpp"

NeuronInput::NeuronInput()
	: m_fActive(false)
	, m_iImpulseTime(0)
	, m_fValue(0)
	, m_fWeight(0)
	, m_fDecayTime(0)
	, m_fDelay(0)
{}

void NeuronInput::activate()
{
	m_fActive = true;
	m_iImpulseTime = 0;
}

void NeuronInput::process()
{
	if(m_fActive)
	{
		m_iImpulseTime += 1;
		// It should be done without expDrop, just assume impulse value as 1.0 and put it after delay.
		// The relaxation drop (recursive) will slowly make it put it down.
		m_fValue = m_fWeight * expDrop((real)m_iImpulseTime - m_fDelay, m_fDecayTime) + expDrop(1.0, 4.0) * m_fValue;

		if(m_iImpulseTime > NEURON_DEACTIVATION_TIME)
		{
			m_fActive = false;
			m_fValue = 0.0;
		}
	}
}

NLib::NSize_t NeuronInput::getParametersCount() const
{
	return 3;
}

void NeuronInput::getParameters(real* opParameters)
{
	opParameters[0] = m_fWeight;
	opParameters[1] = m_fDecayTime;
	opParameters[2] = m_fDelay;
}

void NeuronInput::setParameters(const real* pParameters)
{
	m_fWeight = pParameters[0];
	m_fDecayTime = pParameters[1];
	m_fDelay = pParameters[2];
}