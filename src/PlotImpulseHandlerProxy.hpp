#ifndef SNN_PLOTIMPULSEHANDLERPROXY
#define SNN_PLOTIMPULSEHANDLERPROXY

#include "Simulation/Probes/IImpulseHandler.hpp"
#include "Plots/ImpulsePlot.hpp"

class PlotImpulseHandlerProxy
	: public Simulation::Probes::IImpulseHandler
	, public Plots::ImpulsePlot
{
public:
	PlotImpulseHandlerProxy(Framework::Framework& framework, 
							const NLib::Math::NMVector2f& position, 
							const NLib::Math::NMVector2f& size);

	void setImpulseHandler(Simulation::Probes::IImpulseHandler& impulseHandler)		{ m_pImpulseHandler = &impulseHandler; }

	Simulation::Probes::IImpulseHandler& getImpulseHandler()	{ return *m_pImpulseHandler; }

	virtual void handleImpulse();

private:
	Simulation::Probes::IImpulseHandler* m_pImpulseHandler;
};

typedef std::auto_ptr<PlotImpulseHandlerProxy> PlotImpulseHandlerProxyAPtr;

#endif // SNN_PLOTIMPULSEHANDLERPROXY