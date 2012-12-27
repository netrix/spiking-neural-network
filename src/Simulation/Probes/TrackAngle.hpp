#ifndef SNN_SIMULATION_PROBES_TRACKANGLE
#define SNN_SIMULATION_PROBES_TRACKANGLE

#include "BaseProbe.hpp"
#include "Simulation/Physics/Car.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class TrackAngle
	: public BaseProbe
{
public:
	TrackAngle(Physics::Car& car, Track& track);

	virtual void update(float fDelta);

private:
	Physics::Car& m_car;
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACKANGLE