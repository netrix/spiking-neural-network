#ifndef SNN_SNN_SPIKINGNETWORK
#define SNN_SNN_SPIKINGNETWORK

#include <NLib/Base/nNonCopyable.hpp>
#include <vector>
#include "Common.hpp"
#include "SpikingNeuron.hpp"

namespace SNN {

class SpikingNetwork
	: NLib::NNonCopyable
{
public:
	SpikingNetwork(NLib::NSize_t uNeuronNum, NLib::NSize_t uInputNum, real fStep);
	~SpikingNetwork();

	void handleImpulse(NLib::NSize_t uIndex);

	bool checkOutputImpulse(NLib::NSize_t uIndex) const;

	void update();

	NLib::NSize_t getInputCount() const;
	NLib::NSize_t getOutputCount() const;

	NLib::NSize_t getParametersCount() const;
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	const real m_fStep;
	std::vector<SpikingNeuron*> m_spikingNeurons;
	NLib::NSize_t m_uInputCount;
};

} // SNN

#endif // SNN_SNN_SPIKINGNETWORK