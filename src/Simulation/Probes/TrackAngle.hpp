#ifndef SNN_SIMULATION_PROBES_TRACKANGLE
#define SNN_SIMULATION_PROBES_TRACKANGLE

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"
#include "Simulation/Physics/Car.hpp"
#include "Simulation/Track.hpp"

namespace Simulation {
namespace Probes {

class TrackAngle
	: NLib::NNonCopyable
{
public:
	TrackAngle(Physics::Car& car, Track& track);

	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	void update(float fDelta);

private:
	Physics::Car& m_car;
	Track& m_track;
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_TRACKANGLE