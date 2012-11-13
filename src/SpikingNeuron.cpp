#include "SpikingNeuron.hpp"
#include <NLib/Base/nAssert.hpp>

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

NLib::NSize_t SpikingNeuron::getParametersCount() const
{
	return m_aInputs[0].getParametersCount() * m_aInputs.size() + 3;
}

void SpikingNeuron::getParameters(real* opParameters)
{
	opParameters[0] = m_fDecayTime;
	opParameters[1] = m_fRelaxation;
	opParameters[2] = m_fThreshold; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].getParameters(opParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}

void SpikingNeuron::setParameters(const real* pParameters)
{
	m_fDecayTime = pParameters[0];
	m_fRelaxation = pParameters[1];
	m_fThreshold = pParameters[2]; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].setParameters(pParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}
