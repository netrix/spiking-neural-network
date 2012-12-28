#ifndef SNN_SIMULATION_PASSAGEEVALUATOR
#define SNN_SIMULATION_PASSAGEEVALUATOR

#include <NLib/Base/nNonCopyable.hpp>
#include "Track.hpp"

namespace Simulation {

class PassageEvaluator
	: NLib::NNonCopyable
{
public:
	PassageEvaluator(Track& track);

	void start();

	void update(float fDelta);

	float getTime() const		{ return m_fTime; }
	float getPoints() const		{ return m_fPoints; }

	bool isRunning() const		{ return m_bRunning; }

private:
	float evaluateCarTrackDistance() const;

private:
	Track& m_track;
	float m_fTime;
	float m_fPoints;
	bool m_bRunning;
};

} // Simulation

#endif // SNN_SIMULATION_PASSAGEEVALUATOR