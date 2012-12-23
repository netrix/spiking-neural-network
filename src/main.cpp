#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>
#include "SpikingNeuron.hpp"
#include "Framework/Framework.hpp"
#include "Plots/ImpulsePlotBundle.hpp"
#include "Simulation/World.hpp"
#include "PlotImpulseHandle.hpp"

using namespace std;
using namespace NLib::Math;

const float WORLD_SCALE = 0.2f;
const float STEP = 1.0f / 60.0f;

void setProbesUp(Framework::Framework& framework, Simulation::World& simulationWorld, Plots::ImpulsePlotBundle& plotBundle)
{
	PlotImpulseHandlerAPtr plotCarTrackDistanceA(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 10.0f), NMVector2fLoad(75.0, 10.0f)));
	PlotImpulseHandlerAPtr plotCarTrackDistanceB(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 21.0f), NMVector2fLoad(75.0, 10.0f)));
	PlotImpulseHandlerAPtr plotLeftDistance(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 32.0f), NMVector2fLoad(75.0, 10.0f)));
	PlotImpulseHandlerAPtr plotCarTrackAngle(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 43.0f), NMVector2fLoad(75.0, 10.0f)));
	PlotImpulseHandlerAPtr plotCarTrackSide(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 54.0f), NMVector2fLoad(75.0, 10.0f)));
	PlotImpulseHandlerAPtr plotCarVelocity(new PlotImpulseHandler(framework, NMVector2fLoad(10.0f, 65.0f), NMVector2fLoad(75.0, 10.0f)));

	simulationWorld.setCarTrackDistanceProbeAHandler(*plotCarTrackDistanceA.get());
	simulationWorld.setCarTrackDistanceProbeBHandler(*plotCarTrackDistanceB.get());
	simulationWorld.setLeftDistanceProbeHandler(*plotLeftDistance.get());
	simulationWorld.setCarTrackAngleProbeHandler(*plotCarTrackAngle.get());
	simulationWorld.setCarTrackSideProbeHandle(*plotCarTrackSide.get());
	simulationWorld.setCarVelocityProbeHandler(*plotCarVelocity.get());

	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotCarTrackDistanceA));
	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotCarTrackDistanceB));
	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotLeftDistance));
	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotCarTrackAngle));
	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotCarTrackSide));
	plotBundle.addPlot(Plots::ImpulsePlotAPtr(plotCarVelocity));
}

int SDL_main(int argc, char* args[])
{
	// Setting up framework
	Framework::FrameworkSettings settings = { 800, 600, 32 };
	Framework::Framework framework(settings, WORLD_SCALE);
	framework.setDebugDraw(true);

	// Setting up simulation world
	Simulation::World simulationWorld(framework, WORLD_SCALE, STEP);

	// Images
	Framework::SpriteAPtr car = framework.createSprite("../../data/car.png");
	Framework::SpriteAPtr background = framework.createSprite("../../data/background.png");

	NMVector2f backgroundSize = { 800 * WORLD_SCALE, 600 * WORLD_SCALE};
	background->setSize(backgroundSize);

	NMVector2f offset = -car->getSize() * 0.1f;
	car->setOffset(offset);
	car->setSize(car->getSize() * WORLD_SCALE);

	// Plots
	Plots::ImpulsePlotBundle plotBundle(framework);
	setProbesUp(framework, simulationWorld, plotBundle);

	const Simulation::PassageEvaluator& evaluator = simulationWorld.getPassageEvaluator();
	float fTime = 0.0f;
	float fFixedTimer = 0.0f;
	
	while(framework.update())
	{
		// Drawing
		simulationWorld.draw(*car, *background);
		plotBundle.draw();

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
			simulationWorld.startEvaluation();
			fTime = 0.0f;
		}

		fTime += framework.getTimeDelta();

		//std::cout << track.getCurrentSideFromTrack() << " " << track.getCurrentDistanceFromTrack() << " " << track.getTravelledDistance() << "/" << track.getTrackLength() << std::endl;
		std::cout << "Time: " << evaluator.getTime() << " or " << fTime << ", points: " << evaluator.getPoints() << std::endl;

		fFixedTimer += framework.getTimeDelta();

		if(fFixedTimer > 2.0f)	fFixedTimer += framework.getTimeDelta();

		while(fFixedTimer > STEP)
		{
			fFixedTimer -= STEP;

			if(framework.checkKeyDown(SDLK_w)) simulationWorld.moveForward();
			if(framework.checkKeyDown(SDLK_s)) simulationWorld.moveBackward();
			if(framework.checkKeyDown(SDLK_d)) simulationWorld.turnLeft();
			if(framework.checkKeyDown(SDLK_a)) simulationWorld.turnRight();

			simulationWorld.update();
			plotBundle.update(STEP);
		}

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