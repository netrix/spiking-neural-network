#ifndef SNN_SNN_NEURONINPUT
#define SNN_SNN_NEURONINPUT

#include "Common.hpp"
#include <NLib/Base/nBase.hpp>

namespace SNN {

class NeuronInput
{
public:
	NeuronInput();

	void handleImpulse();

	void update();

	void setWeight(real fWeight)	{ m_fWeight = fWeight; }
	real getWeight() const			{ return m_fWeight; }

	void setDecayTime(real fDecayTime);	
	real getDecayTime() const			{ return m_fDecayTime; }

	void setStep(real fStep);
	real getStep() const			{ return m_fStep; }

	real getImpulseValue() const	{ return m_fValue; }

	static NLib::NSize_t getParametersCount();
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	void calculateRelaxationFactor();

private:
	real m_fInputValue;
	real m_fValue;
	real m_fRelaxationFactor;	// r_ij = exp(-T/tau), T - step, tau - decayTime.

	real m_fWeight;				// w_ij
	real m_fStep;
	real m_fDecayTime;	
};

} // SNN

#endif // SNN_SNN_NEURONINPUT