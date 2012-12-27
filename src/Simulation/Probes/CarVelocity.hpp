#ifndef SNN_SIMULATION_PROBES_CARVELOCITY
#define SNN_SIMULATION_PROBES_CARVELOCITY

#include "BaseProbe.hpp"
#include "Simulation/Physics/Car.hpp"

namespace Simulation {
namespace Probes {

class CarVelocity
	: public BaseProbe
{
public:
	CarVelocity(Physics::Car& car);

	virtual void update(float fDelta);

private:
	Physics::Car& m_car;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_CARVELOCITY