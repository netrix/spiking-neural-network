#ifndef SNN_SPIKING_NEURON
#define SNN_SPIKING_NEURON

#include <vector>
#include <NLib/Base/nBase.hpp>
#include "Common.hpp"
#include "NeuronInput.hpp"

class SpikingNeuron
{
public:
	SpikingNeuron(NLib::NSize_t uInputNum);

	void handleInput(NLib::NSize_t uInput, real value = 1.0);

	void process();

	void setDecayTime(real fDecayTime)	{ m_fDecayTime = fDecayTime; }
	real getDecayTime() const			{ return m_fDecayTime; }

	void setRelaxation(real fRelaxation)	{ m_fRelaxation = fRelaxation; }
	real getRelaxation() const			{ return m_fRelaxation; }

	void setThreshold(real fThreshold)	{ m_fThreshold = fThreshold; }
	real getThreshold() const			{ return m_fThreshold; }

	void setInputWeight(NLib::NSize_t uInput, real fInputWeight)	{ m_aInputs[uInput].setWeight(fInputWeight); }
	real getInputWeight(NLib::NSize_t uInput) const					{ return m_aInputs[uInput].getWeight(); }

	void setInputDecay(NLib::NSize_t uInput, real fInputDecay)	{ m_aInputs[uInput].setDecayTime(fInputDecay); }
	real getInputDecay(NLib::NSize_t uInput) const				{ return m_aInputs[uInput].getDecayTime(); }

	void setInputDelay(NLib::NSize_t uInput, real fInputDelay)	{ m_aInputs[uInput].setDelay(fInputDelay); }
	real getInputDelay(NLib::NSize_t uInput) const				{ return m_aInputs[uInput].getDelay(); }

	real getValue() const		{ return m_fValue; }

	bool isActive() const		{ return m_bActive; }
	bool isImpulse() const		{ return m_iImpulseTime == 0; }

	NLib::NSize_t getParametersCount() const;
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	void operator=(const SpikingNeuron& sn)	{}

private:
	std::vector<NeuronInput> m_aInputs;
	int m_iImpulseTime;
	real m_fValue;
	bool m_bRelaxationActive;
	bool m_bActive;	// To disable unnecessary computing

	real m_fDecayTime;
	real m_fRelaxation;
	real m_fThreshold;
};

#endif // SNN_SPIKING_NEURON
