#ifndef SNN_SIMULATION_WORLD
#define SNN_SIMULATION_WORLD

#include "Framework/Framework.hpp"
#include "Physics/Car.hpp"
#include "Track.hpp"
#include "PassageEvaluator.hpp"
#include "Probes/CarVelocity.hpp"
#include "Probes/TrackAngle.hpp"
#include "Probes/TrackDistance.hpp"
#include "Probes/TrackSide.hpp"
#include "Probes/LeftDistance.hpp"

namespace Simulation {

class World
	: public NLib::NNonCopyable
{
public:
	World(const Framework::Framework& framework, float fWorldScale, float fDelta);

	void saveTrack(const std::string& filePath);
	void loadTrack(const std::string& filePath);

	void resetCar();

	Track&			getTrack()			{ return m_track; }
	const Track&	getTrack() const	{ return m_track; }
		
	void draw(Framework::Sprite& carSprite, Framework::Sprite& backgroundSprite) const;

	void moveForward();
	void moveBackward();
	void turnLeft();
	void turnRight();

	void update();

	// Probes
	void setCarVelocityProbeHandler(Probes::IImpulseHandler& impulseHandler)		{ m_carVelocityProbe.setImpulseHandler(impulseHandler); }
	void setCarTrackAngleProbeHandler(Probes::IImpulseHandler& impulseHandler)		{ m_carTrackAngleProbe.setImpulseHandler(impulseHandler); }
	void setCarTrackDistanceProbeAHandler(Probes::IImpulseHandler& impulseHandler)	{ m_carTrackDistanceProbeA.setImpulseHandler(impulseHandler); }
	void setCarTrackDistanceProbeBHandler(Probes::IImpulseHandler& impulseHandler)	{ m_carTrackDistanceProbeB.setImpulseHandler(impulseHandler); }
	void setCarTrackSideProbeHandle(Probes::IImpulseHandler& impulseHandler)		{ m_carTrackSideProbe.setImpulseHandler(impulseHandler); }
	void setLeftDistanceProbeHandler(Probes::IImpulseHandler& impulseHandler)		{ m_leftTrackDistanceProbe.setImpulseHandler(impulseHandler); }

	Probes::IImpulseHandler& getCarVelocityProbeHandler()			{ return m_carVelocityProbe.getImpulseHandler(); }
	Probes::IImpulseHandler& getCarTrackAngleProbeHandler()			{ return m_carTrackAngleProbe.getImpulseHandler(); }
	Probes::IImpulseHandler& getCarTrackDistanceProbeAHandler()		{ return m_carTrackDistanceProbeA.getImpulseHandler(); }
	Probes::IImpulseHandler& getCarTrackDistanceProbeBHandler()		{ return m_carTrackDistanceProbeB.getImpulseHandler(); }
	Probes::IImpulseHandler& getCarTrackSideProbeHandle()			{ return m_carTrackSideProbe.getImpulseHandler(); }
	Probes::IImpulseHandler& getLeftDistanceProbeHandler()			{ return m_leftTrackDistanceProbe.getImpulseHandler(); }

	void setForwardImpulseHandler(Probes::IImpulseHandler& impulseHandler)		{ m_forwardImpulseHandler = &impulseHandler; }
	void setBackwardImpulseHandler(Probes::IImpulseHandler& impulseHandler)		{ m_backwardImpulseHandler = &impulseHandler; }
	void setLeftImpulseHandler(Probes::IImpulseHandler& impulseHandler)			{ m_leftImpulseHandler = &impulseHandler; }
	void setRightImpulseHandler(Probes::IImpulseHandler& impulseHandler)		{ m_rightImpulseHandler = &impulseHandler; }

	void startEvaluation()	{ m_passageEvaluator.start(); }

	const PassageEvaluator& getPassageEvaluator() const		{ return m_passageEvaluator; }

private:
	void updateProbes();

	void physicsStep(float hz);

	void sendImpulse(Probes::IImpulseHandler* impulseHandler);

private:
	const Framework::Framework& m_framework;
	const float m_fDelta;
	const b2Vec2 m_carStartPosition;
	const float m_carStartOrientation;

	int m_iControlState;

	b2World m_b2World;

	Physics::Car m_car;
	Track m_track;

	// Probes
	Probes::CarVelocity m_carVelocityProbe;			// Probe for car velocity.
	Probes::TrackAngle m_carTrackAngleProbe;		// Probe for angle between car and track.
	Probes::TrackDistance m_carTrackDistanceProbeA;	// Probe from center of the car.
	Probes::TrackDistance m_carTrackDistanceProbeB; // Probe from point in front of the car.
	Probes::TrackSide m_carTrackSideProbe;			// Probe for side of track at which car is.
	Probes::LeftDistance m_leftTrackDistanceProbe;	// Probe of the remaining distance.

	// Input impulse handlers
	Probes::IImpulseHandler* m_forwardImpulseHandler;
	Probes::IImpulseHandler* m_backwardImpulseHandler;
	Probes::IImpulseHandler* m_leftImpulseHandler;
	Probes::IImpulseHandler* m_rightImpulseHandler;

	PassageEvaluator m_passageEvaluator;

private:
	static Physics::MyDestructionListener s_destructionListener;
};

} // Simulation

#endif // SNN_SIMULATION_WORLD