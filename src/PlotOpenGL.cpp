#include "PlotOpenGL.hpp"

using namespace NLib::Math;

PlotOpenGL::PlotOpenGL(const Framework& fw)
	: m_framework(fw)
	, m_margins(NMVector4fLoad(5.0f, 5.0f, 5.0f, 5.0f))
{
}

void PlotOpenGL::drawBasics()
{
	NMVector2f xAxisA = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_size.y - m_margins.z);
	NMVector2f xAxisB = NMVector2fLoad(m_position.x + m_size.x - m_margins.y, m_position.y + m_size.y - m_margins.z);

	NMVector2f yAxisA = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_margins.x);
	NMVector2f yAxisB = NMVector2fLoad(m_position.x + m_margins.w, m_position.y + m_size.y - m_margins.z);

	m_framework.drawRect(m_position, m_size, NMVector4fLoad(0.0f, 0.0f, 0.0f, 0.7f));
	m_framework.drawLine(xAxisA, xAxisB);
	m_framework.drawLine(yAxisA, yAxisB);

	drawArrowhead(yAxisA, NMVector2fLoad(0.0f, -1.5f));
	drawArrowhead(xAxisB, NMVector2fLoad(1.5f, 0.0f));
}

void PlotOpenGL::drawArrowhead(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& direction)
{
	NMVector2f d1 = (position - direction) + NMVector2fLoad(-direction.y, direction.x);
	NMVector2f d2 = (position - direction) + NMVector2fLoad(direction.y, -direction.x);

	m_framework.drawLine(position, d1);
	m_framework.drawLine(position, d2);
}

void PlotOpenGL::drawScale(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, NLib::NSize_t uScale)
{
	//NMVector2f dir = NMVector2fNormalize(p2 - p1);
	//NMVector 
	//float fLength = NMVector2fLength(p2 - p1);
	//float fStep = fLength / uScale;

	//float f = fStep;
	//while(f < fLength)
	//{
	//	m_framework.drawLine(
	//}
}