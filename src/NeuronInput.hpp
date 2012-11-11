#ifndef SNN_NEURON_INPUT
#define SNN_NEURON_INPUT

#include "Common.hpp"

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

	bool isActive() const			{ return m_fActive; }
	real getImpulseValue() const	{ return m_fValue; }

private:
	bool m_fActive;
	int m_iImpulseTime;
	real m_fValue;

	real m_fWeight;
	real m_fDecayTime;
};

#endif // SNN_NEURON_INPUT