/* http://www.iforce2d.net/b2dtut/top-down-car
*/
#ifndef SNN_SIMULATION_PHYSICS_FIXTURE_USER_DATA
#define SNN_SIMULATION_PHYSICS_FIXTURE_USER_DATA

namespace Simulation {
namespace Physics {

//types of fixture user data
enum fixtureUserDataType 
{
    FUD_CAR_TIRE,
    FUD_GROUND_AREA
};

//a class to allow subclassing of different fixture user data
class FixtureUserData 
{
    fixtureUserDataType m_type;
protected:
    FixtureUserData(fixtureUserDataType type) 
        : m_type(type) 
    {}

public:
    virtual fixtureUserDataType getType()	{ return m_type; }

    virtual ~FixtureUserData()				{}
};

//class to allow marking a fixture as a car tire
class CarTireFUD 
    : public FixtureUserData 
{
public:
    CarTireFUD() 
        : FixtureUserData(FUD_CAR_TIRE) 
    {}
};

//class to allow marking a fixture as a ground area
class GroundAreaFUD 
    : public FixtureUserData 
{
public:
    float frictionModifier;
    bool outOfCourse;

    GroundAreaFUD(float fm, bool ooc) 
        : FixtureUserData(FUD_GROUND_AREA) 
    {
        frictionModifier = fm;
        outOfCourse = ooc;
    }
};

// Destruction listener for FUD defined above
class MyDestructionListener
    :  public b2DestructionListener
{
    void SayGoodbye(b2Fixture* fixture)
    {
        if ( FixtureUserData* fud = (FixtureUserData*)fixture->GetUserData() )
            delete fud;
    }

    //(unused but must implement all pure virtual functions)
    void SayGoodbye(b2Joint* joint) {}
};

} // Physics
} // Simulation

#endif // SNN_SIMULATION_PHYSICS_FIXTURE_USER_DATA