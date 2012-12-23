#include "PassageEvaluator.hpp"

namespace {
	const float CHECK_DELTA = 0.5f;
	const float OUTROAD_PENALTY = 100.0f;
}

namespace Simulation {

PassageEvaluator::PassageEvaluator(Track& track)
	: m_track(track)
	, m_fTime(0.0f)
	, m_fCheckTime(0.0f)
	, m_fPoints(0.0f)
	, m_bRunning(false)
{
}

void PassageEvaluator::start()
{
	m_fCheckTime = 0.0f;
	m_fTime = 0.0f;
	m_fPoints = 0.0f;
	m_bRunning = true;
}

void PassageEvaluator::update(float fDelta)
{
	if(m_bRunning)
	{
		m_fCheckTime += fDelta;
		m_fTime += fDelta;

		if(m_fCheckTime > CHECK_DELTA)
		{
			m_fCheckTime -= CHECK_DELTA;

			m_fPoints += evaluateCarTrackDistance();
			m_fPoints += m_track.getTrackLength() - m_track.getTravelledDistance();
		}

		if(m_track.getTravelledDistance() >= m_track.getTrackLength())
		{
			m_bRunning = false;
		}
	}
}

float PassageEvaluator::evaluateCarTrackDistance() const
{
	float fCarTrackDistance = m_track.getCurrentDistanceFromTrack();

	return fCarTrackDistance > m_track.getTrackWidth() ? fCarTrackDistance * OUTROAD_PENALTY : fCarTrackDistance;
}

} // Simulation 
