#include <iostream>
#include <SDL.h>
#include "SpikingNeuron.hpp"

//#include "CarTest.hpp"

using namespace std;

int SDL_main(int argc, char* args[])
{
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

	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Surface* pScreen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

	cout << "Hello" << endl;
	SDL_Quit();
	return 0;
}