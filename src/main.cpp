#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>
#include "SpikingNeuron.hpp"
#include "Framework.hpp"
#include "ImpulsePlot.hpp"
#include "simulation/World.hpp"

using namespace std;
using namespace NLib::Math;

const float WORLD_SCALE = 0.2f;

class ISpikingNeuronInputHandler
{
public:
	virtual void handleInput(NLib::NSize_t uInput) = 0;
};


class ImpulsePlotHandler 
	: public ISpikingNeuronInputHandler
	, NLib::NNonCopyable
{
public:
	ImpulsePlotHandler(ImpulsePlot& plot)
		: m_plot(plot)
	{}

	virtual void handleInput(NLib::NSize_t uInput)
	{
		m_plot.addImpulse();
	}

private:
	ImpulsePlot& m_plot;
};


class TrackDistanceProbe
	: NLib::NNonCopyable
{
public:
	TrackDistanceProbe(Simulation::Track& track, ImpulsePlotHandler& handler)
		: m_track(track)
		, m_handler(handler)
		, m_fLastImpulse(0.0f)
	{
	}

	void update(float fDelta)
	{
		m_fLastImpulse += fDelta;

		float fTrackDistance = m_track.getCurrentDistanceFromTrack();

		if(m_fLastImpulse > (1.0f / fTrackDistance))
		{
			m_handler.handleInput(0);
			m_fLastImpulse  = 0.0f;
		}
	}

private:
	Simulation::Track& m_track;
	ImpulsePlotHandler& m_handler;
	float m_fLastImpulse;
};


int SDL_main(int argc, char* args[])
{
	FrameworkSettings settings = { 800, 600, 32 };
	Framework game(settings, WORLD_SCALE);
	game.setDebugDraw(true);

	Simulation::World simulationWorld(game, WORLD_SCALE);

	SpriteAPtr car = game.createSprite("../../data/car.png");
	SpriteAPtr background = game.createSprite("../../data/background.png");

	// Background sprite
	NMVector2f backgroundSize = { 800 * WORLD_SCALE, 600 * WORLD_SCALE};
	background->setSize(backgroundSize);

	// Offset of car
	NMVector2f offset = -car->getSize() * 0.1f;
	car->setOffset(offset);
	car->setSize(car->getSize() * WORLD_SCALE);

	// Impulse plot
	ImpulsePlot plot(game, NMVector2fLoad(10.0f, 10.0f), NMVector2fLoad(75.0, 10.0f));
	plot.setDrawScale(true);

	ImpulsePlotHandler handler(plot);
	//TrackDistanceProbe prober(track, handler);

	while(game.update())
	{
		simulationWorld.draw(*car, *background);

		// Adding new point to track
		if(game.isMouseButtonLeftClicked())
		{
			NMVector2f mousePos = game.getMouseCoords() * WORLD_SCALE;
		
			if(NMVector2fLength(simulationWorld.getTrack().getLastPoint() - mousePos) > 0.001f)
			{
				simulationWorld.getTrack().addPoint(mousePos);
			}
		}
		// Removing point from track or moving the first point somewhere else
		else if(game.isMouseButtonRightClicked())
		{
			if(simulationWorld.getTrack().getSize() == 1)
			{
				NMVector2f mousePos = game.getMouseCoords() * WORLD_SCALE;
				simulationWorld.getTrack().movePoint(0, mousePos);
			}
			else
			{
				simulationWorld.getTrack().popPoint();
			}
		}

		// Keys
		if(game.checkKeyDown(SDLK_F5))
		{
			simulationWorld.getTrack().saveToFile("simple.txt");
		}
		if(game.checkKeyDown(SDLK_F9))
		{
			simulationWorld.loadTrack("simple.txt");
		}

		//// Prober
		//prober.update(game.getTimeDelta());

		//std::cout << track.getCurrentSideFromTrack() << " " << track.getCurrentDistanceFromTrack() << " " << track.getTravelledDistance() << "/" << track.getTrackLength() << std::endl;

		//// Plot
		//plot.update(game.getTimeDelta());
		//plot.draw();

		if(game.checkKeyDown(SDLK_w)) simulationWorld.moveForward();
		if(game.checkKeyDown(SDLK_s)) simulationWorld.moveBackward();
		if(game.checkKeyDown(SDLK_d)) simulationWorld.turnLeft();
		if(game.checkKeyDown(SDLK_a)) simulationWorld.turnRight();

		simulationWorld.update();

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