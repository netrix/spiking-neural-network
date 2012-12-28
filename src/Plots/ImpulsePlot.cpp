#include "ImpulsePlot.hpp"
#include <algorithm>
using namespace NLib::Math;

namespace Plots {

ImpulsePlot::ImpulsePlot(Framework::Framework& framework, const NMVector2f& position, const NMVector2f& size)
	: m_oglPlot(framework)
	, m_timeWindow(NMVector2fLoad(0.0f, 2.0f))
	, m_fTime(0.0f)
{
	m_oglPlot.setPosition(position);
	m_oglPlot.setSize(size);
}

void ImpulsePlot::addImpulse()
{
	if(m_impulses.empty() || m_fTime > m_impulses.back())
	{
		m_impulses.push_back(m_fTime);

		auto firstInWindow = std::find_if(m_impulses.begin(), m_impulses.end(), [=](float fTime)
		{
			return fTime >= m_timeWindow.x;
		});

		m_impulses.erase(m_impulses.begin(), firstInWindow);
	}
}

void ImpulsePlot::update(float fDelta)
{
	m_fTime += fDelta;

	if(m_fTime > m_timeWindow.y)
	{
		m_timeWindow.x += fDelta;
		m_timeWindow.y += fDelta;
	}
}

void ImpulsePlot::draw()
{
	m_oglPlot.drawImpulses(m_impulses, m_timeWindow);
}

} // Plots