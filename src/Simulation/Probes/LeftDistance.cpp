#include "LeftDistance.hpp"

namespace Simulation {
namespace Probes {

LeftDistance::LeftDistance(Track& track)
	: m_track(track)
{
}

void LeftDistance::update(float fDelta)
{
	float fLeftDistance = 30.0f * m_track.getTrackLength() / (m_track.getTrackLength() - m_track.getTravelledDistance());

	BaseProbe::update(fDelta, fLeftDistance);
}

} // Probes
} // Simulation