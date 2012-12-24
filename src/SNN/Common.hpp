#ifndef SNN_SNN_COMMON
#define SNN_SNN_COMMON

#include <cmath>

namespace SNN {

typedef double real;

const int NEURON_DEACTIVATION_TIME = 0x0fffffff;

inline real H(real fTime)
{
	return fTime <= 0.0 ? 0.0 : 1.0;
}

inline real expDrop(real fTime, real fDecayTime)
{
	return exp(-fTime / fDecayTime);// * H(fTime);
}

} // SNN

#endif // SNN_SNN_COMMON