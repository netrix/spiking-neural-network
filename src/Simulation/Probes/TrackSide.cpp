#include "TrackSide.hpp"

namespace Simulation {
namespace Probes {

TrackSide::TrackSide(Track& track, Enum side)
	: m_track(track)
	, m_side(side)
{
}

void TrackSide::update(float fDelta)
{
	float fSideFreq = 
		m_side == TRACK_SIDE_LEFT && m_track.getCurrentSideFromTrack() < 0.0f ||
		m_side == TRACK_SIDE_RIGHT && m_track.getCurrentSideFromTrack() > 0.0f
		? 100.0f : 0.0f;
	
	BaseProbe::update(fDelta, fSideFreq);
}

} // Probes
} // Simulation

