#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>
#include "SpikingNeuron.hpp"
#include "Framework.hpp"

#include "PhysicsCar.hpp"

//#include "CarTest.hpp"

using namespace std;
using namespace NLib::Math;


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

void tire_vs_groundArea(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began)
{
    PhysicsTire* tire = (PhysicsTire*)tireFixture->GetBody()->GetUserData();
    GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
    if ( began )
        tire->addGroundArea( gaFud );
    else
        tire->removeGroundArea( gaFud );
}

void handleContact(b2Contact* contact, bool began)
{
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    FixtureUserData* fudA = (FixtureUserData*)a->GetUserData();
    FixtureUserData* fudB = (FixtureUserData*)b->GetUserData();

    if ( !fudA || !fudB )
        return;

    if ( fudA->getType() == FUD_CAR_TIRE || fudB->getType() == FUD_GROUND_AREA )
        tire_vs_groundArea(a, b, began);
    else if ( fudA->getType() == FUD_GROUND_AREA || fudB->getType() == FUD_CAR_TIRE )
        tire_vs_groundArea(b, a, began);
}

class MyContactListener
    : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact)
    {
        handleContact(contact, true);
    }

    virtual void EndContact(b2Contact* contact)
    {
        handleContact(contact, false);
    }
};



int SDL_main(int argc, char* args[])
{
    FrameworkSettings settings = { 800, 600, 32 };
    Framework game(settings);

    MyDestructionListener destructionListener;

	b2World& world = game.getPhysicsWorld();
	
	game.setDebugDraw(true);
    world.SetDestructionListener(&destructionListener);

    b2Body* groundBody = null;

    //set up ground areas
    {
        b2BodyDef bodyDef;
        groundBody = world.CreateBody( &bodyDef );

        b2PolygonShape polygonShape;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        fixtureDef.isSensor = true;

        polygonShape.SetAsBox( 9, 7, b2Vec2(-10,15), 20*DEGTORAD );
        b2Fixture* groundAreaFixture = groundBody->CreateFixture(&fixtureDef);
        groundAreaFixture->SetUserData( new GroundAreaFUD( 0.5f, false ) );

        polygonShape.SetAsBox( 9, 5, b2Vec2(5,20), -40*DEGTORAD );
        groundAreaFixture = groundBody->CreateFixture(&fixtureDef);
        groundAreaFixture->SetUserData( new GroundAreaFUD( 0.2f, false ) );
    }

    PhysicsCar physicsCar(&world, 5.0f);
    int controlState = 0;

    SpriteAPtr car = game.createSprite("../../data/car.png");
    SpriteAPtr background = game.createSprite("../../data/background.png");

    // Background sprite
    NMVector2f backgroundSize = { 800, 600 };
    background->setSize(backgroundSize);

    // Offset of car
    NMVector2f offset = -car->getSize() * 0.5f;
    car->setOffset(offset);

    // Car position
    NMVector2f carPos = NMVector2fLoad(126, 578);

    typedef std::vector<NMVector2f> PositionVector;
    PositionVector vPositions;
    vPositions.push_back(carPos);

    NLib::NSize_t uIndex = 0;
    float fProcess = 0.0f;
    float fSpeed = 1.0f;

    float fAngle = 0.0f;
    while(game.update())
    {
        if(game.isMouseButtonLeftClicked())
        {
            NMVector2f mousePos = game.getMouseCoords();

            if(NMVector2fLength(vPositions.back() - mousePos) > 0.001f)
            {
                vPositions.push_back(mousePos);
            }
        }

        if(uIndex < vPositions.size() - 1)
        {
            if(fProcess < 1.0f)
            {
                NMVector2f previous = vPositions[uIndex];
                NMVector2f next = vPositions[uIndex + 1];

                NMVector2f direction = NMVector2fNormalize(next - previous);
                float fLength = NMVector2fLength(next - previous);

                fProcess += fSpeed / fLength;
                carPos += direction * fSpeed;

                fAngle = acosf(NMVector2fDot(NMVector2fLoad(0.0f, -1.0f), direction));
                fAngle = (fAngle * 360.0f) / (2 * NM_PI_F);

                if(direction.x < 0.0f)
                {
                    fAngle = -fAngle;
                }

                std::cout << carPos.x << " " << carPos.y << " " << fLength << " " << uIndex << " "  << vPositions.size() << std::endl;
            }
            else
            {
                uIndex++;
                fProcess = 0.0f;
            }
        }

		controlState = 0;
		controlState |= game.checkKeyDown(SDLK_w) ? TDC_UP : 0;
		controlState |= game.checkKeyDown(SDLK_s) ? TDC_DOWN : 0;
		controlState |= game.checkKeyDown(SDLK_a) ? TDC_RIGHT : 0;
		controlState |= game.checkKeyDown(SDLK_d) ? TDC_LEFT : 0;

		physicsCar.update(controlState);

		game.physicsStep(60.0f);

		b2Vec2 physCarPos = physicsCar.getBody()->GetWorldCenter();
		fAngle = physicsCar.getBody()->GetAngle() * RADTODEG + 180.0f;

        game.drawSprite(0, 0, 0.0f, *background.get());
        game.drawSprite(physCarPos.x, physCarPos.y, fAngle, *car.get());

		world.DrawDebugData();

        game.flipScreen();
    }


    //SpikingNeuron sn(2);
    //sn.setDecayTime(2.0);
    //sn.setRelaxation(5.0);
    //sn.setThreshold(10.0);

    //sn.setInputWeight(0, -5.0);
    //sn.setInputDecay(0, 5.0);

    //sn.setInputWeight(1, 5.0);
    //sn.setInputDecay(1, 5.0);

    //std::vector<real> temp;
    //temp.resize(sn.getParametersCount());

    //sn.getParameters(&temp[0]);

    //for(int i = 0; i < 100; ++i)
    //{
    //	if(i == 10)
    //	{
    //		sn.handleInput(0);
    //	}
    //	if(i > 10 && (i % 4) == 0)
    //	{
    //		sn.handleInput(1);
    //	}	

    //	sn.process();
    //	cout << sn.getValue() << endl;
    //}

    //iforce2d_TopdownCar testbed;
    //testbed.

    //SDL_S* pHelloSurface = null;

    return 0;
}