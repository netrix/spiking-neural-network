#ifndef SNN_SIMULATION_PHYSICS_CONTACTS
#define SNN_SIMULATION_PHYSICS_CONTACTS

#include <Box2D/Box2D.h>

namespace Simulation {
namespace Physics {

class MyContactListener
    : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

} // Physics
} // Simulation

#endif // SNN_SIMULATION_PHYSICS_CONTACTS