#include "LinePlot.hpp"

using namespace NLib::Math;

namespace Plots {

LinePlot::LinePlot(Framework::Framework& framework, const NMVector2f& position, const NMVector2f& size, NLib::NSize_t uMaxSize)
	: m_minMax(NMVector2fLoad(0.0f, 1.0f))
	, m_oglPlot(framework)
{
	m_values.reserve(uMaxSize);
	m_oglPlot.setPosition(position);
	m_oglPlot.setSize(size);
}

void LinePlot::pushValue(float fValue)
{
	m_minMax.y = max(fValue, m_minMax.y);
	m_minMax.x = min(fValue, m_minMax.x);

	if(m_values.size() == m_values.capacity())
	{
		m_values.erase(m_values.begin());
	}

	m_values.push_back(fValue);
}

void LinePlot::draw()
{
	m_oglPlot.drawLines(m_values, m_minMax);
}

} // Plots