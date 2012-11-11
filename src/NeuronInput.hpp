#ifndef SNN_NEURON_INPUT
#define SNN_NEURON_INPUT

#include "Common.hpp"

class NeuronInput
{
public:
	NeuronInput();

	void activate();

	void process();

	real getImpulseValue() const	{ return m_fValue; }

public:
	bool m_fActive;
	int m_iImpulseTime;
	real m_fValue;

	real m_fWeight;
	real m_fDecayTime;
};

#endif // SNN_NEURON_INPUT