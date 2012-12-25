#ifndef SNN_SNN_SPIKINGNEURON
#define SNN_SNN_SPIKINGNEURON

#include <vector>
#include <NLib/Base/nBase.hpp>
#include <NLib/Base/nNonCopyable.hpp>
#include "Common.hpp"
#include "NeuronInput.hpp"

namespace SNN {

class SpikingNeuron
	: NLib::NNonCopyable
{
public:
	SpikingNeuron(NLib::NSize_t uInputNum);

	void handleImpulse(NLib::NSize_t uInput);

	void update();

	void setRefraction(real fRefraction)	{ m_fRefraction = fRefraction; }
	real getRefraction() const				{ return m_fRefraction; }

	void setStep(real fStep);
	real getStep() const					{ return m_fStep; }

	void setOutputDecayTime(real fValueDecayTime);
	real getOutputDecayTime() const				{ return m_fOutputDecayTime; }

	void setValueDecayTime(real fValueDecayTime);
	real getValueDecayTime() const				{ return m_fValueDecayTime; }

	void setThreshold(real fThreshold);
	real getThreshold() const				{ return m_fThreshold; }

	void setInputWeight(NLib::NSize_t uInput, real fInputWeight)	{ m_aInputs[uInput].setWeight(fInputWeight); }
	real getInputWeight(NLib::NSize_t uInput) const					{ return m_aInputs[uInput].getWeight(); }

	void setInputValueDecay(NLib::NSize_t uInput, real fValueDecay)	{ m_aInputs[uInput].setValueDecayTime(fValueDecay); }
	real getInputValueDecay(NLib::NSize_t uInput) const				{ return m_aInputs[uInput].getValueDecayTime(); }

	real getValue() const							{ return m_fValue; }
	real getInputValue(NLib::NSize_t uInput) const	{ return m_aInputs[uInput].getImpulseValue(); }

	bool isImpulse() const		{ return m_fOutput == 1.0f; }

	NLib::NSize_t getParametersCount() const;
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	std::vector<NeuronInput> m_aInputs;
	real m_fValue;
	real m_fOutput;
	real m_fValueRelaxation;
	real m_fOutputRelaxation;

	real m_fRefraction;		// n_0
	real m_fStep;
	real m_fValueDecayTime;
	real m_fOutputDecayTime;
	real m_fThreshold;
};

} // SNN

#endif // SNN_SNN_SPIKINGNEURON
