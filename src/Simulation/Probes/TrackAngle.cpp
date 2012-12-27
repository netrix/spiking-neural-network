#include "TrackAngle.hpp"

using namespace NLib::Math;

namespace Simulation {
namespace Probes {

TrackAngle::TrackAngle(Physics::Car& car, Track& track)
	: m_car(car)
	, m_track(track)
{
}

void TrackAngle::update(float fDelta)
{
	NMVector2f carDir = m_car.getDirection();
	NMVector2f trackDir = m_track.getDirectionOfTrack();

	const float ANGLE_SCALE = 10.0f;
	float fAngle = acosf(NMVector2fDot(carDir, trackDir)) * ANGLE_SCALE;

	BaseProbe::update(fDelta, fAngle);
}

} // Probes
} // Simulation