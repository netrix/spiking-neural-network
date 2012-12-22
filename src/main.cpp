#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>
#include "SpikingNeuron.hpp"
#include "Framework/Framework.hpp"
#include "Plots/ImpulsePlot.hpp"
#include "Simulation/World.hpp"

using namespace std;
using namespace NLib::Math;

const float WORLD_SCALE = 0.2f;
const float STEP = 1.0f / 60.0f;


class ImpulsePlotHandler 
	: public Simulation::Probes::IImpulseHandler
	, public Plots::ImpulsePlot
{
public:
	ImpulsePlotHandler(Framework::Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size)
		: Plots::ImpulsePlot(framework, position, size)
	{}

	virtual void handleImpulse()
	{
		addImpulse();
	}
};



int SDL_main(int argc, char* args[])
{
	Framework::FrameworkSettings settings = { 800, 600, 32 };
	Framework::Framework framework(settings, WORLD_SCALE);
	framework.setDebugDraw(true);

	Simulation::World simulationWorld(framework, WORLD_SCALE, STEP);

	Framework::SpriteAPtr car = framework.createSprite("../../data/car.png");
	Framework::SpriteAPtr background = framework.createSprite("../../data/background.png");

	// Background sprite
	NMVector2f backgroundSize = { 800 * WORLD_SCALE, 600 * WORLD_SCALE};
	background->setSize(backgroundSize);

	// Offset of car
	NMVector2f offset = -car->getSize() * 0.1f;
	car->setOffset(offset);
	car->setSize(car->getSize() * WORLD_SCALE);

	// Impulse plot
	ImpulsePlotHandler plotA(framework, NMVector2fLoad(10.0f, 10.0f), NMVector2fLoad(75.0, 10.0f));
	ImpulsePlotHandler plotB(framework, NMVector2fLoad(10.0f, 21.0f), NMVector2fLoad(75.0, 10.0f));
	ImpulsePlotHandler plotDistance(framework, NMVector2fLoad(10.0f, 32.0f), NMVector2fLoad(75.0, 10.0f));
	

	simulationWorld.setCarTrackDistanceProbeAImpulseHandler(plotA);
	simulationWorld.setCarTrackDistanceProbeBImpulseHandler(plotB);
	simulationWorld.setLeftTrackDistanceProbeImpulseHandler(plotDistance);

	while(framework.update())
	{
		simulationWorld.draw(*car, *background);

		// Adding new point to track
		if(framework.isMouseButtonLeftClicked())
		{
			NMVector2f mousePos = framework.getMouseCoords() * WORLD_SCALE;
		
			if(NMVector2fLength(simulationWorld.getTrack().getLastPoint() - mousePos) > 0.001f)
			{
				simulationWorld.getTrack().addPoint(mousePos);
			}
		}
		// Removing point from track or moving the first point somewhere else
		else if(framework.isMouseButtonRightClicked())
		{
			if(simulationWorld.getTrack().getSize() == 1)
			{
				NMVector2f mousePos = framework.getMouseCoords() * WORLD_SCALE;
				simulationWorld.getTrack().movePoint(0, mousePos);
			}
			else
			{
				simulationWorld.getTrack().popPoint();
			}
		}

		// Keys
		if(framework.checkKeyDown(SDLK_F5))
		{
			simulationWorld.getTrack().saveToFile("simple.txt");
		}
		if(framework.checkKeyDown(SDLK_F9))
		{
			simulationWorld.loadTrack("simple.txt");
		}

		//// Prober
		//prober.update(framework.getTimeDelta());

		//std::cout << track.getCurrentSideFromTrack() << " " << track.getCurrentDistanceFromTrack() << " " << track.getTravelledDistance() << "/" << track.getTrackLength() << std::endl;

		// Plot
		plotA.update(STEP);
		plotA.draw();

		plotB.update(STEP);
		plotB.draw();

		plotDistance.update(STEP);
		plotDistance.draw();

		if(framework.checkKeyDown(SDLK_w)) simulationWorld.moveForward();
		if(framework.checkKeyDown(SDLK_s)) simulationWorld.moveBackward();
		if(framework.checkKeyDown(SDLK_d)) simulationWorld.turnLeft();
		if(framework.checkKeyDown(SDLK_a)) simulationWorld.turnRight();

		simulationWorld.update();

		framework.flipScreen();
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