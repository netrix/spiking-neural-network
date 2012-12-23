#include "TrackAngle.hpp"
#include <iostream>
using namespace NLib::Math;

namespace Simulation {
namespace Probes {

TrackAngle::TrackAngle(Physics::Car& car, Track& track)
	: m_car(car)
	, m_track(track)
	, m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void TrackAngle::update(float fDelta)
{
	m_fLastImpulse += fDelta;

	NMVector2f carDir = m_car.getDirection();
	NMVector2f trackDir = m_track.getDirectionOfTrack();

	const float ANGLE_SCALE = 10.0f;
	float fAngle = acosf(NMVector2fDot(carDir, trackDir)) * ANGLE_SCALE;

	std::cout << fAngle << std::endl;


	if(m_fLastImpulse > (1.0f / fAngle))
	{
		if(m_pImpulseHandler != null)
		{
			m_pImpulseHandler->handleImpulse();
		}
		m_fLastImpulse  = 0.0f;
	}
}

} // Probes
} // Simulation