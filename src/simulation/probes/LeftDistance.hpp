#ifndef SNN_SIMULATION_PROBES_LEFT_DISTANCE
#define SNN_SIMULATION_PROBES_LEFT_DISTANCE

#include "BaseProbe.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class LeftDistance
	: public BaseProbe
{
public:
	LeftDistance(Track& track);

	virtual void update(float fDelta);

private:
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_LEFT_DISTANCE