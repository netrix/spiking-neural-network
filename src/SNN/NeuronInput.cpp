#include "NeuronInput.hpp"
#include <NLib/Base/nAssert.hpp>

namespace SNN {

NeuronInput::NeuronInput()
	: m_fInputValue(0.0f)
	, m_fValue(0.0f)
	, m_fRelaxationFactor(0.0f)
	, m_fWeight(0.0f)
	, m_fStep(0.0f)
	, m_fDecayTime(1.0f)
{}

void NeuronInput::setDecayTime(real fDecayTime)
{ 
	NAssert(fDecayTime > 0.0f, "Decay time must be > 0.0f");
	m_fDecayTime = fDecayTime;

	calculateRelaxationFactor();
}

void NeuronInput::setStep(real fStep)
{
	NAssert(fStep > 0.0f, "Step must be > 0.0f");

	m_fStep = fStep;
	calculateRelaxationFactor();
}

void NeuronInput::calculateRelaxationFactor()
{
	m_fRelaxationFactor = expDrop(m_fStep, m_fDecayTime);
}

void NeuronInput::handleImpulse()
{
	m_fInputValue = 1.0f;
}

void NeuronInput::update()
{
	NAssert(m_fStep > 0.0f, "Step must be > 0.0f");
			
	m_fValue = m_fWeight * m_fInputValue + m_fRelaxationFactor * m_fValue;
	m_fInputValue = 0.0f;
}

NLib::NSize_t NeuronInput::getParametersCount()
{
	return 2;
}

void NeuronInput::getParameters(real* opParameters)
{
	opParameters[0] = m_fWeight;
	opParameters[1] = m_fDecayTime;
}

void NeuronInput::setParameters(const real* pParameters)
{
	m_fWeight = pParameters[0];
	m_fDecayTime = pParameters[1];
}

} // SNN