#ifndef SNN_NEURON_INPUT
#define SNN_NEURON_INPUT

#include "Common.hpp"
#include <NLib/Base/nBase.hpp>

class NeuronInput
{
public:
	NeuronInput();

	void activate();

	void process();

	void setWeight(real fWeight)	{ m_fWeight = fWeight; }
	real getWeight() const			{ return m_fWeight; }

	void setDecayTime(real fDecayTime)	{ m_fDecayTime = fDecayTime; }
	real getDecayTime() const			{ return m_fDecayTime; }

	void setDelay(real fDelay)		{ m_fDelay = fDelay; }
	real getDelay() const			{ return m_fDelay; }

	bool isActive() const			{ return m_fActive; }
	real getImpulseValue() const	{ return m_fValue; }

	NLib::NSize_t getParametersCount() const;
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	bool m_fActive;
	int m_iImpulseTime;
	real m_fValue;

	real m_fWeight;
	real m_fDecayTime;
	real m_fDelay;
};

#endif // SNN_NEURON_INPUT