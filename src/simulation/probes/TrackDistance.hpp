#ifndef SNN_SIMULATION_PROBES_TRACK_DISTANCE
#define SNN_SIMULATION_PROBES_TRACK_DISTANCE

#include "BaseProbe.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class TrackDistance
	: public BaseProbe
{
public:
	TrackDistance(Track& track);

	virtual void update(float fDelta);

private:
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACK_DISTANCE