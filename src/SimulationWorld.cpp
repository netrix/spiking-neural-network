#include "SimulationWorld.hpp"

using namespace NLib::Math;

MyDestructionListener SimulationWorld::s_destructionListener;

SimulationWorld::SimulationWorld(const Framework& framework, float fWorldScale)
	: m_framework(framework)
	, m_iControlState(0)
	, m_b2World(b2Vec2_zero)
	, m_car(m_b2World)
{
	m_b2World.SetDestructionListener(&s_destructionListener);

	// Start position of car
	b2Vec2 carPosition(126, 578);
	carPosition *= fWorldScale;
	m_car.setPosition(carPosition, 180.0f * DEGTORAD);

	// Track setup
	m_track.addPoint(NMVector2fLoad(126, 600) * fWorldScale);
	m_track.setTrackWidth(10.0f);
}

void SimulationWorld::draw(Sprite& carSprite, Sprite& backgroundSprite) const
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
}

void SimulationWorld::update()
{
	static const float STEP = 60.0f;

	m_car.update(m_iControlState);

	physicsStep(STEP);
}

void SimulationWorld::physicsStep(float hz)
{
	float32 timeStep = hz > 0.0f ? 1.0f / hz : float32(0.0f);

	m_b2World.SetAllowSleeping(true);
	m_b2World.SetWarmStarting(true);
	m_b2World.SetContinuousPhysics(true);
	m_b2World.SetSubStepping(false);

	m_b2World.Step(timeStep, 8, 3);
}