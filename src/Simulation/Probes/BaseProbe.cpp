#include "BaseProbe.hpp"
#include <NLib/Base/nBase.hpp>

namespace Simulation {
namespace Probes {

BaseProbe::BaseProbe()
	: m_pImpulseHandler(null)
	, m_fLastImpulse(0.0f)
{
}

void BaseProbe::update(float fDelta, float fFrequency)
{
	m_fLastImpulse += fDelta;

	if(m_fLastImpulse > (1.0f / fFrequency))
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