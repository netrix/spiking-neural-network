#ifndef SNN_PLOTIMPULSEHANDLE
#define SNN_PLOTIMPULSEHANDLE

#include "Simulation/Probes/IImpulseHandler.hpp"
#include "Plots/ImpulsePlot.hpp"

class PlotImpulseHandler 
	: public Simulation::Probes::IImpulseHandler
	, public Plots::ImpulsePlot
{
public:
	PlotImpulseHandler(Framework::Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size);

	virtual void handleImpulse();
};

typedef std::auto_ptr<PlotImpulseHandler> PlotImpulseHandlerAPtr;

#endif // SNN_PLOTIMPULSEHANDLE