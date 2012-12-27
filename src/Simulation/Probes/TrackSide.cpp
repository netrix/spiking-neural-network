#include "TrackSide.hpp"

namespace Simulation {
namespace Probes {

TrackSide::TrackSide(Track& track)
	: m_track(track)
{
}

void TrackSide::update(float fDelta)
{
	float fSideFreq = m_track.getCurrentSideFromTrack() < 0.0f ? 10.0f : 100.0f;
	
	BaseProbe::update(fDelta, fSideFreq);
}

} // Probes
} // Simulation

