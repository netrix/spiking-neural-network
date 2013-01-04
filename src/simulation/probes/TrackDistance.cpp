#include "TrackDistance.hpp"

namespace Simulation {
namespace Probes {

TrackDistance::TrackDistance(Track& track)
	: m_track(track)
{
}

void TrackDistance::setPosition(const NLib::Math::NMVector2f& point)
{
	m_position = point;
}

void TrackDistance::update(float fDelta)
{
	float fTrackDistance = m_track.getDistanceToTrack(m_position);

	BaseProbe::update(fDelta, fTrackDistance);
}

} // Probes
} // Simulation