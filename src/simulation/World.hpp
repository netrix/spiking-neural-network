#ifndef SNN_SIMULATION_WORLD
#define SNN_SIMULATION_WORLD

#include "Framework.hpp"
#include "physics/Car.hpp"
#include "Track.hpp"

namespace Simulation {

class World
	: public NLib::NNonCopyable
{
public:
	World(const Framework& framework, float fWorldScale);

	void loadTrack(const std::string& filePath);

	Track&			getTrack()			{ return m_track; }
	const Track&	getTrack() const	{ return m_track; }
		
	void draw(Sprite& carSprite, Sprite& backgroundSprite) const;

	void moveForward()	{ m_iControlState |= Physics::TDC_UP; }
	void moveBackward()	{ m_iControlState |= Physics::TDC_DOWN; }
	void turnLeft()		{ m_iControlState |= Physics::TDC_LEFT; }
	void turnRight()	{ m_iControlState |= Physics::TDC_RIGHT; }

	void update();

private:
	void physicsStep(float hz);

private:
	const Framework& m_framework;

	int m_iControlState;

	// Box2D
	b2World m_b2World;

	// Simulation
	Physics::Car m_car;
	Track m_track;

private:
	static Physics::MyDestructionListener s_destructionListener;
};

} // Simulation

#endif // SNN_SIMULATION_WORLD