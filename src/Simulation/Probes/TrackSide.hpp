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
	enum Enum
	{
		TRACK_SIDE_LEFT,
		TRACK_SIDE_RIGHT
	};

public:
	TrackSide(Track& track, Enum side);

	virtual void update(float fDelta);

private:
	Enum m_side;
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACKSIDE