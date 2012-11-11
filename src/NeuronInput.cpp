#include "NeuronInput.hpp"

NeuronInput::NeuronInput()
	: m_fActive(false)
	, m_iImpulseTime(0)
	, m_fValue(0)
	, m_fWeight(0)
	, m_fDecayTime(0)
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
		m_fValue = m_fWeight * expDrop((real)m_iImpulseTime, m_fDecayTime);

		if(m_iImpulseTime > NEURON_DEACTIVATION_TIME)
		{
			m_fActive = false;
			m_fValue = 0.0;
		}
	}
}