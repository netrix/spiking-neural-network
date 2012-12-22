#ifndef SNN_SIMULATION_WORLD
#define SNN_SIMULATION_WORLD

#include "Framework.hpp"
#include "Physics/Car.hpp"
#include "Track.hpp"
#include "Probes/TrackDistance.hpp"
#include "Probes/LeftDistance.hpp"

namespace Simulation {

class World
	: public NLib::NNonCopyable
{
public:
	World(const Framework& framework, float fWorldScale, float fDelta);

	void loadTrack(const std::string& filePath);

	Track&			getTrack()			{ return m_track; }
	const Track&	getTrack() const	{ return m_track; }
		
	void draw(Sprite& carSprite, Sprite& backgroundSprite) const;

	void moveForward()	{ m_iControlState |= Physics::TDC_UP; }
	void moveBackward()	{ m_iControlState |= Physics::TDC_DOWN; }
	void turnLeft()		{ m_iControlState |= Physics::TDC_LEFT; }
	void turnRight()	{ m_iControlState |= Physics::TDC_RIGHT; }

	void update();

	// Probes
	void setCarTrackDistanceProbeAImpulseHandler(Probes::IImpulseHandler& impulseHandler)	{ m_carTrackDistanceProbeA.setImpulseHandler(impulseHandler); }
	void setCarTrackDistanceProbeBImpulseHandler(Probes::IImpulseHandler& impulseHandler)	{ m_carTrackDistanceProbeB.setImpulseHandler(impulseHandler); }
	void setLeftTrackDistanceProbeImpulseHandler(Probes::IImpulseHandler& impulseHandler)	{ m_leftTrackDistanceProbe.setImpulseHandler(impulseHandler); }

private:
	void updateProbes();

	void physicsStep(float hz);

private:
	const Framework& m_framework;
	const float m_fDelta;

	int m_iControlState;

	b2World m_b2World;

	Physics::Car m_car;
	Track m_track;

	// Probes
	Probes::TrackDistance m_carTrackDistanceProbeA;	// Probe from center of the car.
	Probes::TrackDistance m_carTrackDistanceProbeB; // Probe from point in front of the car.
	Probes::LeftDistance m_leftTrackDistanceProbe;	// Probe of the remaining distance.

private:
	static Physics::MyDestructionListener s_destructionListener;
};

} // Simulation

#endif // SNN_SIMULATION_WORLD