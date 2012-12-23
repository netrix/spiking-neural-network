#include "CarVelocity.hpp"

namespace Simulation {
namespace Probes {

CarVelocity::CarVelocity(Physics::Car& car)
	: m_car(car)
	, m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void CarVelocity::update(float fDelta)
{
	m_fLastImpulse += fDelta;

	float fCarVelocity = m_car.getBody()->GetLinearVelocity().Length();
	
	if(m_fLastImpulse > (1.0f / fCarVelocity))
	{
		if(m_pImpulseHandler != null)
		{
			m_pImpulseHandler->handleImpulse();
		}
		m_fLastImpulse  = 0.0f;
	}
}

} // Probes
} // Simulation

