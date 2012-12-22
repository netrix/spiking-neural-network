/* http://www.iforce2d.net/b2dtut/top-down-car
*/
#ifndef SNN_SIMULATION_PHYSICS_TIRE
#define SNN_SIMULATION_PHYSICS_TIRE

#include <Box2D/Box2D.h>
#include <set>
#include "FixtureUserData.hpp"

namespace Simulation {
namespace Physics {

enum 
{
	TDC_LEFT     = 0x1,
	TDC_RIGHT    = 0x2,
	TDC_UP       = 0x4,
	TDC_DOWN     = 0x8
};

class Tire 
{
public:
	Tire(b2World* world);
	~Tire();

	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);

	void addGroundArea(GroundAreaFUD* ga);
	void removeGroundArea(GroundAreaFUD* ga);

	void updateTraction();

	b2Vec2 getLateralVelocity();
	b2Vec2 getForwardVelocity();

	void updateFriction();
	void updateDrive(int controlState);
	void updateTurn(int controlState);

	b2Body* getBody()	{ return m_body; }

private:
	b2Body* m_body;
	float m_maxForwardSpeed;
	float m_maxBackwardSpeed;
	float m_maxDriveForce;
	float m_maxLateralImpulse;

	std::set<GroundAreaFUD*> m_groundAreas;
	float m_currentTraction;
};

} // Physics
} // Simulation

#endif // SNN_SIMULATION_PHYSICS_TIRE