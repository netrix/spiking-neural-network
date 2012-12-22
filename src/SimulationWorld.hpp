#ifndef SNN_SIMULATION_WORLD
#define SNN_SIMULATION_WORLD

#include "Framework.hpp"
#include "PhysicsCar.hpp"
#include "Track.hpp"

class SimulationWorld
	: public NLib::NNonCopyable
{
public:
	SimulationWorld(const Framework& framework, float fWorldScale);

	void loadTrack(const std::string& filePath);

	Track&			getTrack()			{ return m_track; }
	const Track&	getTrack() const	{ return m_track; }
		
	void draw(Sprite& carSprite, Sprite& backgroundSprite) const;

	void moveForward()	{ m_iControlState |= TDC_UP; }
	void moveBackward()	{ m_iControlState |= TDC_DOWN; }
	void turnLeft()		{ m_iControlState |= TDC_LEFT; }
	void turnRight()	{ m_iControlState |= TDC_RIGHT; }

	void update();

private:
	void physicsStep(float hz);

private:
	const Framework& m_framework;

	int m_iControlState;

	// Box2D
	b2World m_b2World;

	// Simulation
	PhysicsCar m_car;
	Track m_track;

private:
	static MyDestructionListener s_destructionListener;
};

#endif // SNN_SIMULATION_WORLD