#ifndef SNN_SPIKING_NEURON
#define SNN_SPIKING_NEURON

#include <NLib/Base/nBase.hpp>
#include <NLib/Containers/nArray.hpp>
#include "Common.hpp"
#include "NeuronInput.hpp"

class SpikingNeuron
{
public:
	SpikingNeuron(NLib::NSize_t uInputNum);

	void setThreshold(real fThreshold)	{ m_fThreshold = fThreshold; }

	void handleInput(NLib::NSize_t uInput, real value = 1.0);

	void process();

	bool isImpulse() const	{ return m_iImpulseTime == 0; }

private:
	void operator=(const SpikingNeuron& sn)	{}

private:
	NLib::Containers::NArray<NeuronInput> maInputs;
	int m_iImpulseTime;
	real m_fValue;
	bool mbActive;	// To disable unnecessary computing

	real m_fDecayTime;
	real m_fRelaxation;
	real m_fThreshold;	
};

#endif // SNN_SPIKING_NEURON