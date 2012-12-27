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

	void update();

	NLib::NSize_t getParametersCount() const;
	void getParameters(real* opParameters);
	void setParameters(const real* pParameters);

private:
	const real m_fStep;
	std::vector<SpikingNeuron*> m_spikingNeurons;
};

} // SNN

#endif // SNN_SNN_SPIKINGNETWORK