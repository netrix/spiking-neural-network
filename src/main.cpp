#include <iostream>
#include <SDL.h>
#include "SpikingNeuron.hpp"
#include "Framework.hpp"

//#include "CarTest.hpp"

using namespace std;

int SDL_main(int argc, char* args[])
{
	FrameworkSettings settings = { 800, 600, 32 };
    Framework game(settings);

	SpriteAPtr car = game.createSprite("../../data/car.png");
	SpriteAPtr background = game.createSprite("../../data/background.png");

	// Background sprite
	NLib::Math::NMVector2f backgroundSize = { 800, 600 };
	background->setSize(backgroundSize);

	// Offset of car
	NLib::Math::NMVector2f offset = -car->getSize() * 0.5f;
	car->setOffset(offset);

	float fAngle = 0.0f;
    while(game.update())
    {
		//fAngle += 1.0f;
		game.drawSprite(0, 0, 0.0f, *background.get());
		game.drawSprite(126, 578, fAngle, *car.get());

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