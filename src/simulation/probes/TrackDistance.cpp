#include "TrackDistance.hpp"

namespace Simulation {
namespace Probes {

TrackDistance::TrackDistance(Track& track)
	: m_track(track)
{
}

void TrackDistance::update(float fDelta)
{
	float fTrackDistance = m_track.getCurrentDistanceFromTrack();

	BaseProbe::update(fDelta, fTrackDistance);
}

} // Probes
} // Simulation