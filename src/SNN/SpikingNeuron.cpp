#include "SpikingNeuron.hpp"
#include <NLib/Base/nAssert.hpp>
#include <algorithm>

namespace SNN {

	real m_fRelaxation;

	real m_fRefraction;		// n_0
	real m_fStep;
	real m_fDecayTime;
	real m_fThreshold;

SpikingNeuron::SpikingNeuron(NLib::NSize_t uInputNum)
	: m_aInputs(uInputNum)
	, m_fValue(0.0f)
	, m_fOutput(0.0f)
	, m_fRelaxation(0.0f)
	, m_fStep(0.0f)
	, m_fDecayTime(1.0f)
	, m_fThreshold(0.0)
{
}

void SpikingNeuron::handleImpulse(NLib::NSize_t uInput)
{
	NAssert(uInput < m_aInputs.size(), "Invalid input index");

	m_aInputs[uInput].handleImpulse();
}

void SpikingNeuron::setDecayTime(real fDecayTime)
{ 
	NAssert(fDecayTime > 0.0f, "Decay time must be > 0.0f");
	m_fDecayTime = fDecayTime;

	calculateRelaxationFactor();
}

void SpikingNeuron::setStep(real fStep)
{
	NAssert(fStep > 0.0f, "Step must be > 0.0f");

	m_fStep = fStep;
	calculateRelaxationFactor();

	std::for_each(m_aInputs.begin(), m_aInputs.end(), [fStep](NeuronInput& input)
	{
		input.setStep(fStep);
	});
}

void SpikingNeuron::calculateRelaxationFactor()
{
	m_fRelaxation = expDrop(m_fStep, m_fDecayTime);
}


void SpikingNeuron::update()
{
	// Calculating values from inputs
	real fInputValue = 0.0f;
	std::for_each(m_aInputs.begin(), m_aInputs.end(), [&fInputValue](NeuronInput& input)
	{
		input.update();
		fInputValue += input.getImpulseValue();
	});

	m_fValue = -(m_fRefraction * m_fOutput + m_fRelaxation * m_fValue + m_fThreshold) + fInputValue;

	m_fOutput = m_fValue >= 0.0f ? 1.0f : 0.0f;
}

NLib::NSize_t SpikingNeuron::getParametersCount() const
{
	return NeuronInput::getParametersCount() * m_aInputs.size() + 3;
}

void SpikingNeuron::getParameters(real* opParameters)
{
	opParameters[0] = m_fDecayTime;
	opParameters[1] = m_fRefraction;
	opParameters[2] = m_fThreshold; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].getParameters(opParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}

void SpikingNeuron::setParameters(const real* pParameters)
{
	m_fDecayTime = pParameters[0];
	m_fRefraction = pParameters[1];
	m_fThreshold = pParameters[2]; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].setParameters(pParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}

} // SNN