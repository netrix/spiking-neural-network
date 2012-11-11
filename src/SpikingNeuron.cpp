#include "SpikingNeuron.hpp"
#include <NLib\Base\nAssert.hpp>

SpikingNeuron::SpikingNeuron(NLib::NSize_t uInputNum)
	: m_iImpulseTime(0)
	, m_fValue(0.0)
	, m_bRelaxationActive(false)
	, m_bActive(false)
	, m_fDecayTime(0.0)
	, m_fRelaxation(0.0)
	, m_fThreshold(0.0)
{
	m_aInputs.resize(uInputNum);
}

void SpikingNeuron::handleInput(NLib::NSize_t uInput, real value)
{
	NAssert(uInput < m_aInputs.size(), "Invalid input index");

	if(!m_bRelaxationActive)
	{
		m_aInputs[uInput].activate();
		m_bActive = true;
	}
}

void SpikingNeuron::process()
{
	if(m_bActive)
	{
		real fValue = 0.0;
		bool bActive = false;
		for(int i = 0; i < m_aInputs.size(); ++i)
		{
			NeuronInput& input = m_aInputs[i];
			input.process();
			fValue += input.getImpulseValue();

			bActive = bActive || input.isActive();
		}

		if(!m_bRelaxationActive)
		{
			m_fValue = fValue;
			// Impulse
			if(m_fValue >= m_fThreshold)
			{
				m_iImpulseTime = 0;
				m_bRelaxationActive = true;
			}
		}
		else
		{
			m_iImpulseTime += 1;
			m_fValue = -(m_fRelaxation * expDrop((real)m_iImpulseTime, m_fDecayTime));

			if(m_fValue > -0.1)
			{
				m_bRelaxationActive = false;
			}
		}

		if(!bActive && !m_bRelaxationActive)
		{
			m_bActive = false;
		}
	}
}