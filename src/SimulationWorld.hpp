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

	void draw(Sprite& carSprite, Sprite& backgroundSprite) const;

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