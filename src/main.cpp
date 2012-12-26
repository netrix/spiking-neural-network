#include <iostream>
#include "ApplicationManager.hpp"

int SDL_main(int argc, char* args[])
{
	ApplicationManager app;
	app.run();

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