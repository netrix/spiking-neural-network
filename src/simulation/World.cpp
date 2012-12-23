#include "World.hpp"

using namespace NLib::Math;

namespace Simulation {

Physics::MyDestructionListener World::s_destructionListener;

World::World(const Framework::Framework& framework, float fWorldScale, float fDelta)
	: m_framework(framework)
	, m_iControlState(0)
	, m_fDelta(fDelta)
	, m_b2World(b2Vec2_zero)
	, m_car(m_b2World)
	, m_carTrackAngleProbe(m_car, m_track)
	, m_carTrackDistanceProbeA(m_track)
	, m_carTrackDistanceProbeB(m_track)
	, m_carTrackSideProbe(m_track)
	, m_leftTrackDistanceProbe(m_track)
{
	b2Vec2 carPosition(126, 578);
	NMVector2f trackStart = NMVector2fLoad(126, 600);
	float fTrackWidth = 10.0f;

	m_b2World.SetDestructionListener(&s_destructionListener);
	m_b2World.SetDebugDraw(&m_framework.getDebugDraw());

	// Start position of car
	carPosition *= fWorldScale;
	m_car.setTransform(carPosition, 180.0f * DEGTORAD);

	// Track setup
	m_track.addPoint(trackStart * fWorldScale);
	m_track.setTrackWidth(fTrackWidth);
}

void World::loadTrack(const std::string& filePath)
{
	m_track.loadFromFile(filePath);
}

void World::draw(Framework::Sprite& carSprite, Framework::Sprite& backgroundSprite) const
{
	b2Vec2 physCarPos = m_car.getBody()->GetWorldCenter();
	NMVector2f carPos = NMVector2fLoad(physCarPos.x, physCarPos.y);
	float fAngle = m_car.getBody()->GetAngle() * RADTODEG + 180.0f;

	static const NMVector3f TRACK_COLOR = NMVector3fLoad(0.88f, 0.58f, 0.58f);
	static const NMVector3f CAR_TRACK_COLOR = NMVector3fLoad(1.0f, 0.0f, 0.0f);
	static const NMVector3f CAR_TRACK_ARROW_COLOR = NMVector3fLoad(0.0f, 1.0f, 0.0f);

	m_framework.drawSprite(0, 0, 0.0f, backgroundSprite);
	m_framework.drawSprite(physCarPos.x, physCarPos.y, fAngle, carSprite);
	m_framework.drawLineStrip(m_track.getTrackLineStripPoints());
	m_framework.drawTriangleStrip(m_track.getTrackTriangleStripPoints(), TRACK_COLOR);
		
	m_framework.drawLine(m_track.getCurrentPosition(), m_track.getCurrentPointOnTrack(), CAR_TRACK_COLOR);
	m_framework.drawArrow(m_track.getCurrentPointOnTrack(), m_track.getDirectionOfTrack(), CAR_TRACK_ARROW_COLOR);

	m_b2World.DrawDebugData();
}

void World::update()
{
	m_car.update(m_iControlState);
	
	physicsStep(1.0f / m_fDelta);
	updateProbes();

	m_iControlState = 0;
}

void World::updateProbes()
{
	const float PROBE_DISTANCE = 10.0f;

	// Probe for angle between car and track
	m_carTrackAngleProbe.update(m_fDelta);

	// Probe from the point in front of the car
	m_track.setCurrentPosition(m_car.getPosition() + m_car.getDirection() * PROBE_DISTANCE);	// TODO: There's a bug with setting two points, track handles properly only one point
	m_carTrackDistanceProbeB.update(m_fDelta);

	// Probe from the point of car position
	m_track.setCurrentPosition(m_car.getPosition());
	m_carTrackDistanceProbeA.update(m_fDelta);

	// Probe for side between car and track
	m_carTrackSideProbe.update(m_fDelta);

	// Distance left probe
	m_leftTrackDistanceProbe.update(m_fDelta);
}

void World::physicsStep(float hz)
{
	float32 timeStep = hz > 0.0f ? 1.0f / hz : float32(0.0f);

	m_b2World.SetAllowSleeping(true);
	m_b2World.SetWarmStarting(true);
	m_b2World.SetContinuousPhysics(true);
	m_b2World.SetSubStepping(false);

	m_b2World.Step(timeStep, 8, 3);
}

} // Simulation