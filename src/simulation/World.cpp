#include "World.hpp"

using namespace NLib::Math;

namespace Simulation {

Physics::MyDestructionListener World::s_destructionListener;

World::World(const Framework& framework, float fWorldScale, float fDelta)
	: m_framework(framework)
	, m_iControlState(0)
	, m_fDelta(fDelta)
	, m_b2World(b2Vec2_zero)
	, m_car(m_b2World)
	, m_trackDistanceProbe(m_track)
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

void World::draw(Sprite& carSprite, Sprite& backgroundSprite) const
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
		
	m_framework.drawLine(carPos, m_track.getCurrentPointOnTrack(), CAR_TRACK_COLOR);
	m_framework.drawArrow(m_track.getCurrentPointOnTrack(), m_track.getDirectionOfTrack(), CAR_TRACK_ARROW_COLOR);

	m_b2World.DrawDebugData();
}

void World::update()
{
	m_car.update(m_iControlState);
	m_track.setCurrentPosition(m_car.getPosition());

	physicsStep(1.0f / m_fDelta);

	// Probes
	m_trackDistanceProbe.update(m_fDelta);

	m_iControlState = 0;
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