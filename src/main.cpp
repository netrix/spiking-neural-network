#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>
#include "SpikingNeuron.hpp"
#include "Framework.hpp"
#include "ImpulsePlot.hpp"

#include "PhysicsCar.hpp"
#include "PhysicsContacts.hpp"
#include "Track.hpp"


using namespace std;
using namespace NLib::Math;

const float WORLD_SCALE = 0.2f;


class TrackDistanceProbe
{
public:
	TrackDistanceProbe();



private:
};



int SDL_main(int argc, char* args[])
{
    FrameworkSettings settings = { 800, 600, 32 };
    Framework game(settings, WORLD_SCALE);

	b2World& world = game.getPhysicsWorld();
	
	MyDestructionListener destructionListener;
    world.SetDestructionListener(&destructionListener);

	game.setDebugDraw(true);

    //PhysicsCar physicsCar(&world, 5.0f);
	PhysicsCar physicsCar(&world);
	physicsCar.setPosition(b2Vec2(126 * WORLD_SCALE, 578 * WORLD_SCALE) , 180.0f * DEGTORAD);

    int controlState = 0;

    SpriteAPtr car = game.createSprite("../../data/car.png");
    SpriteAPtr background = game.createSprite("../../data/background.png");

    // Background sprite
    NMVector2f backgroundSize = { 800 * WORLD_SCALE, 600 * WORLD_SCALE};
    background->setSize(backgroundSize);

    // Offset of car
    NMVector2f offset = -car->getSize() * 0.1f;
    car->setOffset(offset);
	car->setSize(car->getSize() * WORLD_SCALE);

	// Track
	Track track;
	track.addPoint(NMVector2fLoad(126, 600) * WORLD_SCALE);
	track.setTrackWidth(10.0f);

	// Impulse plot
	ImpulsePlot plot(game, NMVector2fLoad(10.0f, 10.0f), NMVector2fLoad(75.0, 10.0f));
	plot.setDrawScale(true);

	float fWindowTime = 0.0f;

    while(game.update())
    {
		b2Vec2 physCarPos = physicsCar.getBody()->GetWorldCenter();
		float fAngle = physicsCar.getBody()->GetAngle() * RADTODEG + 180.0f;

        game.drawSprite(0, 0, 0.0f, *background.get());
        game.drawSprite(physCarPos.x, physCarPos.y, fAngle, *car.get());
		game.drawLineStrip(track.getTrackLineStripPoints());
		game.drawTriangleStrip(track.getTrackTriangleStripPoints(), NMVector3fLoad(0.88f, 0.58f, 0.58f));
		
		// Adding new point to track
        if(game.isMouseButtonLeftClicked())
        {
            NMVector2f mousePos = game.getMouseCoords() * WORLD_SCALE;

			if(NMVector2fLength(track.getLastPoint() - mousePos) > 0.001f)
            {
				track.addPoint(mousePos);
            }
        }
		// Removing point from track or moving the first point somewhere else
		else if(game.isMouseButtonRightClicked())
		{
			if(track.getSize() == 1)
			{
				NMVector2f mousePos = game.getMouseCoords() * WORLD_SCALE;
				track.movePoint(0, mousePos);
			}
			else
			{
				track.popPoint();
			}
		}

		if(game.checkKeyDown(SDLK_F5))
		{
			track.saveToFile("simple.txt");
		}

		if(game.checkKeyDown(SDLK_F9))
		{
			track.loadFromFile("simple.txt");
		}

		if(game.checkKeyDown(SDLK_i))
		{
			plot.addImpulse();
		}


		NMVector2f carPos = NMVector2fLoad(physCarPos.x, physCarPos.y);
		track.setCurrentPosition(carPos);

		game.drawLine(carPos, track.getCurrentPointOnTrack(), NLib::Math::NMVector3fLoad(1.0f, 0.0f, 0.0f));
		
		std::cout << track.getCurrentSideFromTrack() << " " << track.getCurrentDistanceFromTrack() << " " << track.getTravelledDistance() << "/" << track.getTrackLength() << std::endl;

		game.drawArrow(track.getCurrentPointOnTrack(), track.getDirectionOfTrack(), NMVector3fLoad(0.0f, 1.0f, 0.0f));

		// Plot
		plot.update(game.getTimeDelta());
		plot.draw();

		controlState = 0;
		controlState |= game.checkKeyDown(SDLK_w) ? TDC_UP : 0;
		controlState |= game.checkKeyDown(SDLK_s) ? TDC_DOWN : 0;
		controlState |= game.checkKeyDown(SDLK_a) ? TDC_RIGHT : 0;
		controlState |= game.checkKeyDown(SDLK_d) ? TDC_LEFT : 0;

		physicsCar.update(controlState);

		game.physicsStep(60.0f);

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