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
	SpikingNetwork(real fStep);
	~SpikingNetwork();

	void addNeuron(SpikingNeuronAPtr neuron);

	void handleImpulse(NLib::NSize_t uIndex);

	void update();

private:
	const real m_fStep;
	std::vector<SpikingNeuron*> m_spikingNeurons;
};

} // SNN

#endif // SNN_SNN_SPIKINGNETWORK