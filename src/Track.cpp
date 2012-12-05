#include "Track.hpp"
using namespace NLib::Math;

NMVector2f getNormalizedPerpendicularVector(const NMVector2f& vec)
{
	NMVector2f v = NMVector2fNormalize(vec);
	return NMVector2fLoad(-v.y, v.x);
}


Track::Track()
	: m_fTrackWidth(0.0f)
	, m_uCurrentPoint(0)
{
}

void Track::addPoint(const NLib::Math::NMVector2f& point)
{
	m_vPathPoints.push_back(point);
}

NLib::NSize_t Track::getSize() const
{
	return m_vPathPoints.size();
}

const NLib::Math::NMVector2f& Track::getPoint(NLib::NSize_t uIndex) const
{
	return m_vPathPoints.at(uIndex);
}

const NLib::Math::NMVector2f& Track::last() const
{
	return m_vPathPoints.back();
}

void Track::clear()
{
	return m_vPathPoints.clear();
}

void Track::setTrackWidth(float fTrackWidth)
{
	m_fTrackWidth = fTrackWidth;
}

float Track::getTrackWidth() const
{
	return m_fTrackWidth;
}

float Track::getTrackLength() const
{
	float fLength = 0.0f;

	for(NLib::NSize_t i = 1; i < m_vPathPoints.size(); ++i)
	{
		fLength += NMVector2fLength(m_vPathPoints[i] - m_vPathPoints[i - 1]);
	}

	return fLength;
}

void Track::setCurrentPosition(const NLib::Math::NMVector2f& point)
{
}

float Track::getCurrentDistance() const
{
	return 0.0f;
}

const PointVector& Track::getTrackLineStripPoints() const
{
	return m_vPathPoints;
}

PointVector Track::getTrackTriangleStripPoints() const
{
	PointVector vStripPoints;

	if(m_vPathPoints.size() < 2)
	{
		return vStripPoints;
	}

	// First 2 points
	NMVector2f v = getNormalizedPerpendicularVector(m_vPathPoints[1] - m_vPathPoints[0]) * m_fTrackWidth;
	vStripPoints.push_back(m_vPathPoints[0] + v);
	vStripPoints.push_back(m_vPathPoints[0] - v);

	// All points in the middle
	for(NLib::NSize_t i = 1; i < m_vPathPoints.size() - 1; ++i)
	{
		NMVector2f v1 = m_vPathPoints[i] - m_vPathPoints[i - 1];
		NMVector2f v2 = m_vPathPoints[i + 1] - m_vPathPoints[i];
		NMVector2f n = getNormalizedPerpendicularVector(v1 + v2) * m_fTrackWidth;
		
		vStripPoints.push_back(m_vPathPoints[i] + n);
		vStripPoints.push_back(m_vPathPoints[i] - n);
	}

	//  Last 2 points
	NLib::NSize_t uLastIndex = m_vPathPoints.size() - 1;
	v = getNormalizedPerpendicularVector(m_vPathPoints[uLastIndex] - m_vPathPoints[uLastIndex - 1]) * m_fTrackWidth;
	vStripPoints.push_back(m_vPathPoints[uLastIndex] + v);
	vStripPoints.push_back(m_vPathPoints[uLastIndex] - v);

	return vStripPoints;
}
