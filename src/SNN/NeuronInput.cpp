#include "NeuronInput.hpp"
#include <NLib/Base/nAssert.hpp>

namespace SNN {

NeuronInput::NeuronInput()
	: m_fInputValue(0.0f)
	, m_fValue(0.0f)
	, m_fValueRelaxation(0.0f)
	, m_fWeight(0.0f)
	, m_fStep(0.0f)
	, m_fValueDecayTime(1.0f)
{}

void NeuronInput::setValueDecayTime(real fValueDecayTime)
{ 
	NAssert(fValueDecayTime > 0.0f, "Decay time must be > 0.0f");
	m_fValueDecayTime = fValueDecayTime;

	m_fValueRelaxation = calculateRelaxationFactor(m_fStep, fValueDecayTime);
}

void NeuronInput::setStep(real fStep)
{
	NAssert(fStep > 0.0f, "Step must be > 0.0f");

	m_fStep = fStep;
	m_fValueRelaxation = calculateRelaxationFactor(m_fStep, m_fValueDecayTime);
}

void NeuronInput::handleImpulse()
{
	m_fInputValue = 1.0f;
}

void NeuronInput::update()
{
	NAssert(m_fStep > 0.0f, "Step must be > 0.0f");
			
	m_fValue = m_fWeight * m_fInputValue + m_fValueRelaxation * m_fValue;
	m_fInputValue = 0.0f;
}

void NeuronInput::reset()
{
	m_fValue = 0.0f;
}

NLib::NSize_t NeuronInput::getParametersCount()
{
	return 2;
}

void NeuronInput::getParameters(real* opParameters) const
{
	opParameters[0] = m_fWeight;
	opParameters[1] = m_fValueDecayTime;
}

void NeuronInput::setParameters(const real* pParameters)
{
	m_fWeight = pParameters[0];
	m_fValueDecayTime = pParameters[1];

	m_fValueRelaxation = calculateRelaxationFactor(m_fStep, m_fValueDecayTime);
	m_fValue = 0.0f;
}

float NeuronInput::evaluateParameters() const
{
	return m_fValueDecayTime > 0.0f ? 0.0f : 1.0f;
}

} // SNN