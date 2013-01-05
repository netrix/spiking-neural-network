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

	void setPosition(const NLib::Math::NMVector2f& point);

	virtual void update(float fDelta);

private:
	NLib::Math::NMVector2f m_position;
	Track& m_track;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACK_DISTANCE