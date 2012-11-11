#include "NeuronInput.hpp"

NeuronInput::NeuronInput()
	: m_fActive(false)
	, m_iImpulseTime(0x7fffffff)
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
	m_fValue = m_fWeight * expDrop((real)m_iImpulseTime, m_fDecayTime);
}