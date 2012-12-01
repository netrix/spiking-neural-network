#include <iostream>
#include <SDL.h>
#include "SpikingNeuron.hpp"
#include "Game.hpp"

//#include "CarTest.hpp"

using namespace std;

int SDL_main(int argc, char* args[])
{
	GameSettings settings = { 800, 600, 32 };

    Game game(settings);

    //RGBUint8 colorKey = { 255

    ImageAPtr car = game.createImage("../../data/car.png");
	//ImageAPtr car = game.createImage("C:\\Users\\Netrix\\Documents\\Programming\\C++\\current\\snn\\data\\car.png");

    while(game.update())
    {
		game.drawImage(50, 50, *car.get());

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