#include "TrackSide.hpp"

namespace Simulation {
namespace Probes {

TrackSide::TrackSide(Track& track)
	: m_track(track)
	, m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void TrackSide::update(float fDelta)
{
	m_fLastImpulse += fDelta;

	float fSideFreq = m_track.getCurrentSideFromTrack() < 0.0f ? 10.0f : 100.0f;
	
	if(m_fLastImpulse > (1.0f / fSideFreq))
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

