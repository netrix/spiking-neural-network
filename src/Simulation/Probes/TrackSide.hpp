#ifndef SNN_SIMULATION_PROBES_TRACKSIDE
#define SNN_SIMULATION_PROBES_TRACKSIDE

#include "BaseProbe.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

/** \brief Class that probes the angle of track for car.
 * 
 * It generates an impulse with 10 Hz if car is on the left side and 100 Hz when car is on the right side.
 */
class TrackSide
	: public BaseProbe
{
public:
	TrackSide(Track& track);

	virtual void update(float fDelta);

private:
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACKSIDE