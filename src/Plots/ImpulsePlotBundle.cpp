#include "ImpulsePlotBundle.hpp"

using namespace NLib;

namespace Plots {

ImpulsePlotBundle::ImpulsePlotBundle(Framework::Framework& framework)
	: m_framework(framework)
{
}

ImpulsePlotBundle::~ImpulsePlotBundle()
{
	std::for_each(m_plots.begin(), m_plots.end(), [](ImpulsePlot*& pPlot) 
		{ 
			delete pPlot;
		}
	);
}

ImpulsePlot& ImpulsePlotBundle::createPlot(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size)
{
	NSize_t uIndex = m_plots.size();

	m_plots.push_back(new ImpulsePlot(m_framework, position, size));

	return *m_plots[uIndex];
}

void ImpulsePlotBundle::addPlot(ImpulsePlotAPtr plot)
{
	m_plots.push_back(plot.release());
}

void ImpulsePlotBundle::update(float fDelta)
{
	std::for_each(m_plots.begin(), m_plots.end(), [fDelta](ImpulsePlot*& pPlot) 
		{ 
			pPlot->update(fDelta); 
		}
	);
}

void ImpulsePlotBundle::draw()
{
	std::for_each(m_plots.begin(), m_plots.end(), [](ImpulsePlot*& pPlot) 
		{ 
			pPlot->draw(); 
		}
	);
}

} // Plots