#ifndef SNN_SIMULATION_PROBES_BASEPROBE
#define SNN_SIMULATION_PROBES_BASEPROBE

#include <NLib/Base/nNonCopyable.hpp>
#include "IImpulseHandler.hpp"

namespace Simulation {
namespace Probes {

class BaseProbe
	: NLib::NNonCopyable
{
public:
	void setImpulseHandler(IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	IImpulseHandler& getImpulseHandler()						{ return *m_pImpulseHandler; }

	virtual void update(float fDelta) = 0;

	virtual void reset();

protected:
	BaseProbe();

	void update(float fDelta, float fFrequency);

private:
	IImpulseHandler* m_pImpulseHandler;
	float m_fLastImpulse;
};

} // Probes
} // Simulation

#endif	// SNN_SIMULATION_PROBES_BASEPROBE