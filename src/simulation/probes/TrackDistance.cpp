#include "TrackDistance.hpp"

namespace Simulation {
namespace Probes {

TrackDistance::TrackDistance(Track& track)
	: m_track(track)
	, m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void TrackDistance::update(float fDelta)
{
	m_fLastImpulse += fDelta;

	float fTrackDistance = m_track.getCurrentDistanceFromTrack();

	if(m_fLastImpulse > (1.0f / fTrackDistance))
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