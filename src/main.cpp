#include <iostream>
#include "SpikingNeuron.hpp"


using namespace std;



int main()
{
	SpikingNeuron sn(2);
	sn.setDecayTime(2.0);
	sn.setRelaxation(5.0);
	sn.setThreshold(10.0);

	sn.setInputWeight(0, -5.0);
	sn.setInputDecay(0, 5.0);

	sn.setInputWeight(1, 5.0);
	sn.setInputDecay(1, 5.0);

	for(int i = 0; i < 100; ++i)
	{
		if(i == 10)
		{
			sn.handleInput(0);
		}
		if(i > 10 && (i % 4) == 0)
		{
			sn.handleInput(1);
		}

		sn.process();
		cout << sn.getValue() << endl;
	}


	cout << "Hello" << endl;
	return 0;
}