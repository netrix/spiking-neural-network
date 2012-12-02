#ifndef SNN_PHYSICS_TIRE
#define SNN_PHYSICS_TIRE

#include <Box2D/Box2D.h>
#include <set>
#include "PhysicsFixtureUserData.hpp"

enum 
{
	TDC_LEFT     = 0x1,
	TDC_RIGHT    = 0x2,
	TDC_UP       = 0x4,
	TDC_DOWN     = 0x8
};


class PhysicsTire 
{
public:
	PhysicsTire(b2World* world, float fScale);
	~PhysicsTire();

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

#endif // SNN_PHYSICS_TIRE