#ifndef SNN_SIMULATION_PROBES_TRACKSIDE
#define SNN_SIMULATION_PROBES_TRACKSIDE

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

/** \brief Class that probes the angle of track for car.
 * 
 * It generates an impulse with 10 Hz if car is on the left side and 100 Hz when car is on the right side.
 */
class TrackSide
	: NLib::NNonCopyable
{
public:
	TrackSide(Track& track);

	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	void update(float fDelta);

private:
	Track& m_track;
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACKSIDE