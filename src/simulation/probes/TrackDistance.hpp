#ifndef SNN_SIMULATION_PROBES_TRACK_DISTANCE
#define SNN_SIMULATION_PROBES_TRACK_DISTANCE

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class TrackDistance
	: NLib::NNonCopyable
{
public:
	TrackDistance(Track& track);

	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	void update(float fDelta);

private:
	Track& m_track;
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif