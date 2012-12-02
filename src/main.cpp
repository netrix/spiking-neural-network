#include <iostream>
#include <vector>
#include "SpikingNeuron.hpp"
#include "Framework.hpp"

//#include "CarTest.hpp"

using namespace std;
using namespace NLib::Math;

int SDL_main(int argc, char* args[])
{
	FrameworkSettings settings = { 800, 600, 32 };
    Framework game(settings);

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

		//fAngle += 1.0f;
		game.drawSprite(0, 0, 0.0f, *background.get());
		game.drawSprite(carPos.x, carPos.y, fAngle, *car.get());

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