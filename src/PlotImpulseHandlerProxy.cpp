#include "PlotImpulseHandlerProxy.hpp"

using namespace NLib::Math;

PlotImpulseHandlerProxy::PlotImpulseHandlerProxy(Framework::Framework& framework, 
												const NLib::Math::NMVector2f& position, 
												const NLib::Math::NMVector2f& size)
	: Plots::ImpulsePlot(framework, position, size)
	, m_pImpulseHandler(null)
{
}

void PlotImpulseHandlerProxy::handleImpulse()
{
	addImpulse();

	if(m_pImpulseHandler != null)
	{
		m_pImpulseHandler->handleImpulse();
	}
}