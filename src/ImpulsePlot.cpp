#include "ImpulsePlot.hpp"

using namespace NLib::Math;

ImpulsePlot::ImpulsePlot(Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size)
	: m_oglPlot(framework)
	, m_timeWindow(NMVector2fLoad(0.0f, 2.0f))
	, m_fTime(0.0f)
{
	m_oglPlot.setPosition(position);
	m_oglPlot.setSize(size);
}

void ImpulsePlot::addImpulse()
{
	m_impulses.push_back(m_fTime);
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