#include "LeftDistance.hpp"

namespace Simulation {
namespace Probes {

LeftDistance::LeftDistance(Track& track)
	: m_track(track)
	, m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void LeftDistance::update(float fDelta)
{
	m_fLastImpulse += fDelta;

	float fLeftDistance = m_track.getTrackLength() - m_track.getTravelledDistance();

	if(m_fLastImpulse > (1.0f / fLeftDistance))
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