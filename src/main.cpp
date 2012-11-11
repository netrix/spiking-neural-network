#include <iostream>
#include "SpikingNeuron.hpp"


using namespace std;



int main()
{
	SpikingNeuron sn(1);

	for(int i = 0; i < 2000; ++i)
	{
		sn.process();
	}


	cout << "Hello" << endl;
	return 0;
}