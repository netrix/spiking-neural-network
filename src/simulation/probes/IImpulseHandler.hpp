#ifndef SNN_SIMULATION_PROBES_IIMPULSEHANDLER
#define SNN_SIMULATION_PROBES_IIMPULSEHANDLER

namespace Simulation {
namespace Probes {

class IImpulseHandler
{
public:
	virtual void handleImpulse() = 0;
};

} // Probes
} // Simulation

#endif // SNN_SIMULATION_PROBES_IIMPULSEHANDLER