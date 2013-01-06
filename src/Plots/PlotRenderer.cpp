#include "PlotRenderer.hpp"
#include <algorithm>

using namespace NLib;
using namespace Math;

namespace Plots {

PlotRenderer::PlotRenderer(const Framework::Framework& fw)
	: m_framework(fw)
	, m_margins(NMVector4fLoad(2.0f, 2.0f, 2.0f, 2.0f))
	, m_bDrawScale(false)
	, m_bNeedRecalculation(true)
	, m_fScaleLengthX(0.0f)
	, m_fScaleLengthY(0.0f)
{
	m_plotColor = NMVector3fLoad(0.5f, 0.5f, 1.0f);
}

void PlotRenderer::drawImpulses(const FloatVector& times, const NLib::Math::NMVector2f& timeWindow)
{
	drawBasics();

	// Calculate times to draw
	auto first = std::find_if(times.begin(), times.end(), [timeWindow](float a){ return a >= timeWindow.x; });
	auto last = std::find_if(times.begin(), times.end(), [timeWindow](float a){ return a >= timeWindow.y; });

	const float IMPULSE_HEIGHT = 4.0f;
	float fScaleFactor = m_fScaleLengthX / (timeWindow.y - timeWindow.x);

	NMVector2f impulseA = m_yAxisA;
	NMVector2f impulseB = m_yAxisA + NMVector2fNormalize(m_yAxisB - m_yAxisA) * IMPULSE_HEIGHT;

	// Basic impulse points
	for(auto it = first; it != times.end(); ++it)
	{
		float fOffset = (*it - timeWindow.x) * fScaleFactor;

		m_framework.drawLine(impulseA + NMVector2fLoad(fOffset, 0.0f), impulseB + NMVector2fLoad(fOffset, 0.0f), m_plotColor);
	}
}

void PlotRenderer::drawLines(const FloatVector& values, const NLib::Math::NMVector2f& minMax)
{
	drawBasics();

	float fMin = min(minMax.x, 0.0f);
	float fStepX = m_fScaleLengthX / values.capacity();
	float fStepY = m_fScaleLengthY / (minMax.y - fMin);

	Framework::PointVector points;
	points.reserve(values.size());

	// Basic impulse points
	for(NLib::NSize_t i = 0; i < values.size(); ++i)
	{
		float fX = fStepX * i + m_xAxisA.x;
		float fY = m_xAxisA.y - (fStepY * (values[i] - fMin));

		points.push_back(NMVector2fLoad(fX, fY));
	}

	if(fMin < 0.0f)
	{
		m_framework.drawLine(m_xAxisA + NMVector2fLoad(0.0f, fMin * fStepY), m_xAxisB + NMVector2fLoad(0.0f, fMin * fStepY));
	}

	if(!values.empty())
	{
		m_framework.drawLineStrip(points, m_plotColor);
	}
}

void PlotRenderer::drawBasics()
{
	if(m_bNeedRecalculation)
	{
		calculateBasics();
	}

	m_framework.drawRect(m_position, m_size, NMVector4fLoad(0.0f, 0.0f, 0.0f, 0.7f));
	m_framework.drawLine(m_xAxisA, m_xAxisB);
	m_framework.drawLine(m_yAxisA, m_yAxisB);

	drawArrowhead(m_yAxisB, NMVector2fLoad(0.0f, -1.5f));
	drawArrowhead(m_xAxisB, NMVector2fLoad(1.5f, 0.0f));

	if(m_bDrawScale)
	{
		drawScaleStep(m_xAxisA, m_xAxisB, 5.0);
		drawScaleStep(m_yAxisA, m_yAxisB, 5.0);
	}
}

void PlotRenderer::calculateBasics()
{
	m_xAxisA = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_size.y - m_margins.z);
	m_xAxisB = NMVector2fLoad(m_position.x + m_size.x - m_margins.y, m_position.y + m_size.y - m_margins.z);

	m_yAxisA = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_size.y - m_margins.z);
	m_yAxisB = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_margins.x);
	

	m_fScaleLengthX = NMVector2fLength(m_xAxisB - m_xAxisA);
	m_fScaleLengthY = NMVector2fLength(m_yAxisB - m_yAxisA);
}

void PlotRenderer::drawArrowhead(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& direction)
{
	NMVector2f d1 = (position - direction) + NMVector2fLoad(-direction.y, direction.x);
	NMVector2f d2 = (position - direction) + NMVector2fLoad(direction.y, -direction.x);

	m_framework.drawLine(position, d1);
	m_framework.drawLine(position, d2);
}

void PlotRenderer::drawScale(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, int iScale)
{
	float fStep = NMVector2fLength(p2 - p1) / iScale;
	drawScaleStep(p1, p2, fStep);
}

void PlotRenderer::drawScaleStep(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, float fStep)
{
	NMVector2f dir = NMVector2fNormalize(p2 - p1);
	float fLength = NMVector2fLength(p2 - p1) - 1.0f;

	NMVector2f pA = NMVector2fLoad(-dir.y, dir.x);
	NMVector2f pB = NMVector2fLoad(dir.y, -dir.x);

	float f = fStep;
	while(f < fLength)
	{
		NMVector2f step = dir * f;
		m_framework.drawLine(p1 + pA + step, p1 + pB + step);
		f += fStep;
	}
}

} // Plots
