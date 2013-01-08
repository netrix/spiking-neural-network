#include <iostream>
#include "ApplicationManager.hpp"

#ifdef main
	#undef main
#endif

int main(int argc, char* args[])
{
	ApplicationManager app;
	app.run();

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
	//	linePlot.draw();
	//	linePlotInputA.draw();

	//	// Adding new point to track
	//	if(framework.isMouseButtonLeftClicked())
	//	{
	//		sn.handleImpulse(0);
	//	}
	//	// Removing point from track or moving the first point somewhere else
	//	else if(framework.isMouseButtonRightClicked())
	//	{
	//		sn.handleImpulse(1);
	//	}

		//	while(fFixedTimer > STEP)
	//	{
	//		sn.update();


	//		// Plot test
	//		linePlot.pushValue(sn.getValue());
	//		linePlotInputA.pushValue(sn.getInputValue(0));
	//		
	//		std::cout << sn.isImpulse() << " " << sn.getValue() << " " << sn.getInputValue(0) << std::endl;
	//	}
	//}

	return 0;
}
