#ifndef SNN_SIMULATION_PROBES_LEFT_DISTANCE
#define SNN_SIMULATION_PROBES_LEFT_DISTANCE

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class LeftDistance
	: NLib::NNonCopyable
{
public:
	LeftDistance(Track& track);

	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	void update(float fDelta);

private:
	Track& m_track;
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_LEFT_DISTANCE