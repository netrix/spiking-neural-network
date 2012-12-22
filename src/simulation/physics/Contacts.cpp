#include "Contacts.hpp"
#include "Tire.hpp"

namespace Simulation {
namespace Physics {

void tire_vs_groundArea(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began)
{
	Tire* tire = (Tire*)tireFixture->GetBody()->GetUserData();
	GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
	if ( began )
	{
		tire->addGroundArea( gaFud );
	}
	else
	{
		tire->removeGroundArea( gaFud );
	}
}

void handleContact(b2Contact* contact, bool began)
{
	b2Fixture* a = contact->GetFixtureA();
	b2Fixture* b = contact->GetFixtureB();
	FixtureUserData* fudA = (FixtureUserData*)a->GetUserData();
	FixtureUserData* fudB = (FixtureUserData*)b->GetUserData();

	if ( !fudA || !fudB )
	{
		return;
	}

	if ( fudA->getType() == FUD_CAR_TIRE || fudB->getType() == FUD_GROUND_AREA )
	{
		tire_vs_groundArea(a, b, began);
	}
	else if ( fudA->getType() == FUD_GROUND_AREA || fudB->getType() == FUD_CAR_TIRE )
	{
		tire_vs_groundArea(b, a, began);
	}
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	handleContact(contact, true);
}

void MyContactListener::EndContact(b2Contact* contact)
{
	handleContact(contact, false);
}

} // Physics
} // Simulation