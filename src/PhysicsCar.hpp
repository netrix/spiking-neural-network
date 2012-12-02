#ifndef SNN_PHYSICS_CAR
#define SNN_PHYSICS_CAR

#include <Box2D/Box2D.h>
#include <vector>
#include "PhysicsTire.hpp"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

class PhysicsCar 
{
public:
    PhysicsCar(b2World* world, float fScale);

    ~PhysicsCar();

    void update(int controlState);

	b2Body* getBody()		{ return m_body; }

private:
    b2Body* m_body;
    std::vector<PhysicsTire*> m_tires;
    b2RevoluteJoint *flJoint, *frJoint;
};

#endif // SNN_PHYSICS_CAR