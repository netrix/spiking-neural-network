#include "SpikingNeuron.hpp"
#include <NLib/Base/nAssert.hpp>
#include <algorithm>

namespace SNN {

SpikingNeuron::SpikingNeuron(NLib::NSize_t uInputNum)
	: m_aInputs(uInputNum)
	, m_fValue(0.0f)
	, m_fOutput(0.0f)
	, m_fValueRelaxation(0.0f)
	, m_fOutputRelaxation(0.0f)
	, m_fStep(0.0f)
	, m_fValueDecayTime(1.0f)
	, m_fOutputDecayTime(1.0f)
	, m_fThreshold(0.0)
{
}

void SpikingNeuron::handleImpulse(NLib::NSize_t uInput)
{
	NAssert(uInput < m_aInputs.size(), "Invalid input index");

	m_aInputs[uInput].handleImpulse();
}

void SpikingNeuron::setOutputDecayTime(real fDecayTime)
{ 
	NAssert(fDecayTime > 0.0f, "Decay time must be > 0.0f");
	m_fOutputDecayTime = fDecayTime;

	m_fOutputRelaxation = calculateRelaxationFactor(m_fStep, fDecayTime);
}

void SpikingNeuron::setValueDecayTime(real fDecayTime)
{ 
	NAssert(fDecayTime > 0.0f, "Decay time must be > 0.0f");
	m_fValueDecayTime = fDecayTime;

	m_fValueRelaxation = calculateRelaxationFactor(m_fStep, fDecayTime);
}

void SpikingNeuron::setStep(real fStep)
{
	NAssert(fStep > 0.0f, "Step must be > 0.0f");

	m_fStep = fStep;

	m_fOutputRelaxation = calculateRelaxationFactor(m_fStep, m_fOutputDecayTime);
	m_fValueRelaxation = calculateRelaxationFactor(m_fStep, m_fValueDecayTime);

	std::for_each(m_aInputs.begin(), m_aInputs.end(), [fStep](NeuronInput& input)
	{
		input.setStep(fStep);
	});
}

void SpikingNeuron::setThreshold(real fThreshold)
{ 
	m_fThreshold = fThreshold; 
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

	m_fValue = m_fValueRelaxation * m_fValue + fInputValue - m_fRefraction * m_fOutput - m_fThreshold;
	m_fOutput *= m_fOutputRelaxation;

	m_fOutput = m_fValue >= 0.0f ? 1.0f : m_fOutput;
}

NLib::NSize_t SpikingNeuron::getParametersCount() const
{
	return NeuronInput::getParametersCount() * m_aInputs.size() + 4;
}

void SpikingNeuron::getParameters(real* opParameters)
{
	opParameters[0] = m_fOutputDecayTime;
	opParameters[1] = m_fValueDecayTime;
	opParameters[2] = m_fRefraction;
	opParameters[3] = m_fThreshold; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].getParameters(opParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}

void SpikingNeuron::setParameters(const real* pParameters)
{
	m_fOutputDecayTime = pParameters[0];
	m_fValueDecayTime = pParameters[1];
	m_fRefraction = pParameters[2];
	m_fThreshold = pParameters[3]; 

	for(NLib::NSize_t i = 0; i < m_aInputs.size(); ++i)
	{
		m_aInputs[i].setParameters(pParameters + m_aInputs[i].getParametersCount() * i + 3);
	}
}

} // SNN