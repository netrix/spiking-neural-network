#include "PlotImpulseHandle.hpp"

using namespace NLib::Math;

PlotImpulseHandler::PlotImpulseHandler(Framework::Framework& framework, const NMVector2f& position, const NMVector2f& size)
	: Plots::ImpulsePlot(framework, position, size)
{
}

void PlotImpulseHandler::handleImpulse()
{
	addImpulse();
}