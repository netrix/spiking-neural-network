#include "CarVelocity.hpp"

namespace Simulation {
namespace Probes {

CarVelocity::CarVelocity(Physics::Car& car)
	: m_car(car)
{
}

void CarVelocity::update(float fDelta)
{
	float fCarVelocity = m_car.getBody()->GetLinearVelocity().Length();

	BaseProbe::update(fDelta, fCarVelocity);
}

} // Probes
} // Simulation

