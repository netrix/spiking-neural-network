#include <iostream>
#include "SpikingNeuron.hpp"


using namespace std;



int main()
{
	SpikingNeuron sn(2);
	sn.setDecayTime(10.0);
	sn.setRelaxation(20.0);
	sn.setThreshold(20.0);

	sn.setInputWeight(0, -5.0);
	sn.setInputDecay(0, 5.0);

	sn.setInputWeight(1, 5.0);
	sn.setInputDecay(1, 5.0);

	for(int i = 0; i < 2000; ++i)
	{
		if(i == 10)
		{
			sn.handleInput(0);
		}
		if(i == 15)
		{
			sn.handleInput(1);
		}

		sn.process();
		cout << sn.getValue() << endl;
	}


	cout << "Hello" << endl;
	return 0;
}