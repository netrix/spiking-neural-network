#ifndef SNN_PHYSICS_CONTACTS
#define SNN_PHYSICS_CONTACTS

#include <Box2D/Box2D.h>

class MyContactListener
    : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

#endif