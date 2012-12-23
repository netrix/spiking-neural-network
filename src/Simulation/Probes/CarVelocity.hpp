#ifndef SNN_SIMULATION_PROBES_CARVELOCITY
#define SNN_SIMULATION_PROBES_CARVELOCITY

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"
#include "Simulation/Physics/Car.hpp"

namespace Simulation {
namespace Probes {

class CarVelocity
	: NLib::NNonCopyable
{
public:
	CarVelocity(Physics::Car& car);

	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	void update(float fDelta);

private:
	Physics::Car& m_car;
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_CARVELOCITY