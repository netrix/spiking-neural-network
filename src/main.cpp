#include <iostream>
#include "Framework/Framework.hpp"
#include "Plots/ImpulsePlotBundle.hpp"
#include "Plots/LinePlot.hpp"
#include "Simulation/World.hpp"
#include "PlotImpulseHandle.hpp"

#include "SNN/SpikingNeuron.hpp"
#include "ApplicationManager.hpp"

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


class TrackRecorder
{
public:
	TrackRecorder();

private:
};



class NeuralNetworkControlelr
{
public:
private:
};

class UserController
{
public:
private:
};


int SDL_main(int argc, char* args[])
{
	ApplicationManager app;
	app.run();

	//// Setting up framework
	//Framework::FrameworkSettings settings = { 800, 600, 32 };
	//Framework::Framework framework(settings, WORLD_SCALE);
	//framework.setDebugDraw(true);

	//// Setting up simulation world
	//Simulation::World simulationWorld(framework, WORLD_SCALE, STEP);

	//// Images
	//Framework::SpriteAPtr car = framework.createSprite("../../data/car.png");
	//Framework::SpriteAPtr background = framework.createSprite("../../data/background.png");

	//NMVector2f backgroundSize = { 800 * WORLD_SCALE, 600 * WORLD_SCALE};
	//background->setSize(backgroundSize);

	//NMVector2f offset = -car->getSize() * 0.1f;
	//car->setOffset(offset);
	//car->setSize(car->getSize() * WORLD_SCALE);

	//// Plots
	//Plots::ImpulsePlotBundle plotBundle(framework);	
	//setProbesUp(framework, simulationWorld, plotBundle);

	//const Simulation::PassageEvaluator& evaluator = simulationWorld.getPassageEvaluator();
	//float fTime = 0.0f;
	//float fFixedTimer = 0.0f;

	//// Neural network
	//SNN::SpikingNeuron sn(2);
	//sn.setOutputDecayTime(10.0f);
	//sn.setValueDecayTime(30.0);
	//sn.setRefraction(10.0);
	//sn.setThreshold(0.5);
	//sn.setStep(1);

	//sn.setInputWeight(0, 0.4);
	//sn.setInputValueDecay(0, 10.0);

	//sn.setInputWeight(1, 0.4);
	//sn.setInputValueDecay(1, 5.0);

	//// Line plot
	//Plots::LinePlot linePlot(framework,  NMVector2fLoad(90.0f, 10.0f),  NMVector2fLoad(60.0f, 50.0f), 160);
	//Plots::LinePlot linePlotInputA(framework,  NMVector2fLoad(90.0f, 65.0f),  NMVector2fLoad(60.0f, 50.0f), 160);
	//
	//while(framework.update())
	//{
	//	// Drawing
	//	simulationWorld.draw(*car, *background);
	//	plotBundle.draw();
	//	linePlot.draw();
	//	linePlotInputA.draw();

	//	// Adding new point to track
	//	if(framework.isMouseButtonLeftClicked())
	//	{
	//		//NMVector2f mousePos = framework.getMouseCoords() * WORLD_SCALE;
	//	
	//		//if(NMVector2fLength(simulationWorld.getTrack().getLastPoint() - mousePos) > 0.001f)
	//		//{
	//		//	simulationWorld.getTrack().addPoint(mousePos);
	//		//}
	//		sn.handleImpulse(0);
	//	}
	//	// Removing point from track or moving the first point somewhere else
	//	else if(framework.isMouseButtonRightClicked())
	//	{
	//		//if(simulationWorld.getTrack().getSize() == 1)
	//		//{
	//		//	NMVector2f mousePos = framework.getMouseCoords() * WORLD_SCALE;
	//		//	simulationWorld.getTrack().movePoint(0, mousePos);
	//		//}
	//		//else
	//		//{
	//		//	simulationWorld.getTrack().popPoint();
	//		//}
	//		sn.handleImpulse(1);
	//	}

	//	// Keys
	//	if(framework.checkKeyDown(SDLK_F5))
	//	{
	//		simulationWorld.saveTrack("../../data/simple_track.txt");
	//	}
	//	if(framework.checkKeyDown(SDLK_F9))
	//	{
	//		simulationWorld.loadTrack("../../data/simple_track.txt");
	//		simulationWorld.startEvaluation();
	//		fTime = 0.0f;
	//	}
	//	if(framework.checkKeyDown(SDLK_ESCAPE))
	//	{
	//			break;
	//	}

	//	if(framework.checkKeyDown(SDLK_PLUS))
	//	{
	//		sn.setOutputDecayTime(sn.getOutputDecayTime() + 0.1f);
	//	}
	//	if(framework.checkKeyDown(SDLK_MINUS))
	//	{
	//		sn.setOutputDecayTime(sn.getOutputDecayTime() - 0.1f);
	//	}

	//	fTime += framework.getTimeDelta();

	//	//std::cout << track.getCurrentSideFromTrack() << " " << track.getCurrentDistanceFromTrack() << " " << track.getTravelledDistance() << "/" << track.getTrackLength() << std::endl;
	//	//std::cout << "Time: " << evaluator.getTime() << " or " << fTime << ", points: " << evaluator.getPoints() << std::endl;

	//	fFixedTimer += framework.getTimeDelta();

	//	if(fFixedTimer > 2.0f)	fFixedTimer += framework.getTimeDelta();

	//	while(fFixedTimer > STEP)
	//	{
	//		fFixedTimer -= STEP;

	//		if(framework.checkKeyDown(SDLK_w)) simulationWorld.moveForward();
	//		if(framework.checkKeyDown(SDLK_s)) simulationWorld.moveBackward();
	//		if(framework.checkKeyDown(SDLK_d)) simulationWorld.turnLeft();
	//		if(framework.checkKeyDown(SDLK_a)) simulationWorld.turnRight();

	//		sn.update();


	//		// Plot test
	//		linePlot.pushValue(sn.getValue());
	//		linePlotInputA.pushValue(sn.getInputValue(0));
	//		
	//		std::cout << sn.isImpulse() << " " << sn.getValue() << " " << sn.getInputValue(0) << std::endl;

	//		simulationWorld.update();
	//		plotBundle.update(STEP);
	//	}

	//	framework.flipScreen();
	//}

	return 0;
}