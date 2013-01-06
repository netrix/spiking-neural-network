#include "Track.hpp"
#include <NLib/Base/nAssert.hpp>
#include <fstream>

using namespace NLib;
using namespace Math;

namespace Simulation {

NMVector2f getNormalizedPerpendicularVector(const NMVector2f& vec)
{
	NMVector2f v = NMVector2fNormalize(vec);
	return NMVector2fLoad(-v.y, v.x);
}

NMVector2f getProjectedPointOnVector(const NMVector2f& pA, const NMVector2f& pB, const NMVector2f& pSrc)
{
	NAssert(NMVector2fLength(pB - pA) != 0.0f, "pA and pB doesn't define line");

	NMVector2f vAB = pB - pA;
	NMVector2f vASrc = pSrc - pA;

	float fLengthASrc = NMVector2fLength(vASrc);

	vAB = NMVector2fNormalize(vAB);
	vASrc = NMVector2fNormalize(vASrc);
	
	float fCos = NMVector2fDot(vAB, vASrc);

	return pA + vAB * fLengthASrc * fCos;
}




Track::Track()
	: m_fTrackWidth(0.0f)
	, m_uCurrentPoint(0)
	, m_fMaxTrackDistance(-1.0f)
{
}

void Track::addPoint(const NLib::Math::NMVector2f& point)
{
	m_vPathPoints.push_back(point);
}

void Track::movePoint(NLib::NSize_t uIndex, const NLib::Math::NMVector2f& point)
{
	m_vPathPoints.at(uIndex) = point;
}

void Track::popPoint()
{
	if(m_vPathPoints.size() < 2)
	{
		return;
	}

	if(m_uCurrentPoint == m_vPathPoints.size() - 1)
	{
		m_uCurrentPoint--;
	}

	m_vPathPoints.pop_back();
}

bool Track::isAtStart() const
{
	return m_bIsPointCloser && m_uCurrentPoint == 0;
}

bool Track::isAtEnd() const
{
	return m_bIsPointCloser && m_uCurrentPoint == m_vPathPoints.size() - 1;
}

NLib::NSize_t Track::getSize() const
{
	return m_vPathPoints.size();
}

const NLib::Math::NMVector2f& Track::getPoint(NLib::NSize_t uIndex) const
{
	return m_vPathPoints.at(uIndex);
}

const NLib::Math::NMVector2f& Track::getLastPoint() const
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

void Track::setMaxTrackDistance(float fMaxTrackDistance)
{
	m_fMaxTrackDistance = fMaxTrackDistance;
}

float Track::getMaxTrackDistance() const
{
	return m_fMaxTrackDistance;
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

NLib::NSize_t Track::findClosestPoint(const NMVector2f& point) const
{
	NAssert(!m_vPathPoints.empty(), "m_vPathPoints cannot be empty");

	NLib::NSize_t uMinIndex = 0;
	float fMinLength = NMVector2fLength(point - m_vPathPoints[uMinIndex]);

	for(NLib::NSize_t i = 1; i < m_vPathPoints.size(); ++i)
	{
		float fLength = NMVector2fLength(point - m_vPathPoints[i]);

		if(fLength < fMinLength)
		{
			fMinLength = fLength;
			uMinIndex = i;
		}
	}

	return uMinIndex;
}

NLib::NSize_t Track::findClosestPointAround(NLib::NSize_t uIndex, const NMVector2f& point)
{
	NAssert(!m_vPathPoints.empty(), "m_vPathPoints cannot be empty");

	// Current point
	NLib::NSize_t uMinIndex = uIndex;
	float fMinLength = NMVector2fLength(point - m_vPathPoints[uMinIndex]);

	// Previous point
	if(uIndex != 0)
	{
		float fLength = NMVector2fLength(point - m_vPathPoints[uIndex - 1]);

		if(fLength < fMinLength)
		{
			fMinLength = fLength;
			uMinIndex = uIndex - 1;
		}
	}

	// Next point
	if(uIndex + 1 != m_vPathPoints.size())
	{
		float fLength = NMVector2fLength(point - m_vPathPoints[uIndex + 1]);

		if(fLength < fMinLength)
		{
			//fMinLength = fLength;
			uMinIndex = uIndex + 1;
		}
	}

	return uMinIndex;
}

void Track::setCurrentPositionFromStart(const NLib::Math::NMVector2f& point)
{
	m_uCurrentPoint = 0;
	setCurrentPosition(point);
}

float Track::getDistanceToTrack(const NLib::Math::NMVector2f& point) const
{
	// Closest point on path to given point
	NLib::NSize_t uClosestPoint = findClosestPoint(point);
	float fDistanceToPoint = NMVector2fLength(point - m_vPathPoints[uClosestPoint]);
	
	// Closest vector on path to given point
	NLib::NSize_t uClosestVector = NMAX_SIZE_T;
	float fDistanceToVector = fDistanceToPoint;
	NMVector2f closestProjection = m_vPathPoints[uClosestPoint];
	for(NLib::NSize_t i = 1; i < m_vPathPoints.size(); ++i)
	{
		NMVector2f pA = m_vPathPoints[i - 1];
		NMVector2f pB = m_vPathPoints[i];

		NMVector2f projection = getProjectedPointOnVector(pA, pB, point);
		float fAB = NMVector2fLength(pA - pB);
		float fAP = NMVector2fLength(pA - projection);
		float fBP = NMVector2fLength(pB - projection);

		if(fAP < fAB && fBP < fAB)
		{
			float fPP = NMVector2fLength(point - projection);

			if(fPP < fDistanceToVector)
			{
				fDistanceToVector = fPP;
				uClosestVector = i;
				closestProjection = projection;
			}
		}
	}

	return min(fDistanceToPoint, fDistanceToVector);
}

void Track::setCurrentPosition(const NLib::Math::NMVector2f& point)
{
	m_currentPosition = point;

	// Closest point around on path to given point
	NLib::NSize_t uClosestPoint = findClosestPointAround(m_uCurrentPoint, point);
	float fDistanceToPoint = NMVector2fLength(point - m_vPathPoints[uClosestPoint]);

	// Closest vector around on path to given point
	NLib::NSize_t uClosestVector = m_uCurrentPoint;
	float fDistanceToVector = fDistanceToPoint;
	NMVector2f closestProjection = m_vPathPoints[uClosestPoint];

	// Check previous vector
	if(m_uCurrentPoint != 0)
	{
		NMVector2f pA = m_vPathPoints[m_uCurrentPoint - 1];
		NMVector2f pB = m_vPathPoints[m_uCurrentPoint];

		NMVector2f projection = getProjectedPointOnVector(pA, pB, point);
		float fAB = NMVector2fLength(pA - pB);
		float fAP = NMVector2fLength(pA - projection);
		float fBP = NMVector2fLength(pB - projection);

		if(fAP < fAB && fBP < fAB)
		{
			float fPP = NMVector2fLength(point - projection);

			if(fPP < fDistanceToVector)
			{
				fDistanceToVector = fPP;
				uClosestVector = m_uCurrentPoint;
				closestProjection = projection;
			}
		}
	}

	// Check next vector
	if(m_uCurrentPoint + 1 < m_vPathPoints.size())
	{
		NMVector2f pA = m_vPathPoints[m_uCurrentPoint];
		NMVector2f pB = m_vPathPoints[m_uCurrentPoint + 1];

		NMVector2f projection = getProjectedPointOnVector(pA, pB, point);
		float fAB = NMVector2fLength(pA - pB);
		float fAP = NMVector2fLength(pA - projection);
		float fBP = NMVector2fLength(pB - projection);

		if(fAP < fAB && fBP < fAB)
		{
			float fPP = NMVector2fLength(point - projection);

			if(fPP < fDistanceToVector)
			{
				fDistanceToVector = fPP;
				uClosestVector = m_uCurrentPoint + 1;
				closestProjection = projection;
			}
		}
	}
	
	if(m_fMaxTrackDistance < 0.0f || min(fDistanceToPoint, fDistanceToVector) <= m_fMaxTrackDistance)
	{
		// Choose closest vector or point
		if(fDistanceToPoint > fDistanceToVector)
		{
			m_bIsPointCloser = false;
			m_currentPointOnTrack = closestProjection;
			m_uCurrentPoint = uClosestVector;
		}
		else
		{
			m_bIsPointCloser = true;
			m_currentPointOnTrack = m_vPathPoints[uClosestPoint];
			m_uCurrentPoint = uClosestPoint;
		}
	}
}

float Track::getCurrentDistanceFromTrack() const
{
	return NMVector2fLength(m_currentPosition - m_currentPointOnTrack);
}

float Track::getCurrentSideFromTrack() const
{
	if(m_vPathPoints.size() < 2)
	{
		return 0.0f;
	}

	NMVector2f v1 = NMVector2fNormalize(m_currentPosition - m_currentPointOnTrack);
	NMVector2f v2;

	if(m_uCurrentPoint != 0)
	{
		v2 = NMVector2fNormalize(m_vPathPoints[m_uCurrentPoint] - m_vPathPoints[m_uCurrentPoint - 1]);
	}
	else
	{
		v2 = NMVector2fNormalize(m_vPathPoints[1] - m_vPathPoints[0]);
	}

	NMVector2f vW = NMVector2fLoad(-v2.y, v2.x) - v1;
	
	return NMVector2fLength(vW) < 1.0f ? 1.0f : -1.0f;
}

const PointVector& Track::getTrackLineStripPoints() const
{
	return m_vPathPoints;
}

const NLib::Math::NMVector2f& Track::getCurrentPointOnTrack() const
{
	return m_currentPointOnTrack;
}

NLib::Math::NMVector2f Track::getDirectionOfTrack() const
{
	if(m_vPathPoints.size() < 2 || (m_bIsPointCloser && m_uCurrentPoint == m_vPathPoints.size() - 1))
	{
		return NMVector2fLoadZeros();
	}
	else if(m_uCurrentPoint == 0)
	{
		return NMVector2fNormalize(m_vPathPoints[1] - m_vPathPoints[0]);
	}
	else if(m_bIsPointCloser)
	{
		return NMVector2fNormalize(m_vPathPoints[m_uCurrentPoint + 1] - m_vPathPoints[m_uCurrentPoint]);
	}
	else
	{
		return NMVector2fNormalize(m_currentPointOnTrack - m_vPathPoints[m_uCurrentPoint - 1]);
	}
}

float Track::getTravelledDistance() const
{
	float fCurrentLength = 0.0f;
	NLib::NSize_t uTraveledDistance = m_bIsPointCloser ? m_uCurrentPoint + 1 : m_uCurrentPoint;

	for(NLib::NSize_t i = 1; i < uTraveledDistance; ++i)
	{
		fCurrentLength += NMVector2fLength(m_vPathPoints[i] - m_vPathPoints[i - 1]);
	}

	return m_bIsPointCloser ? fCurrentLength : fCurrentLength + NMVector2fLength(m_vPathPoints[m_uCurrentPoint - 1] - m_currentPointOnTrack);
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

void Track::saveToFile(const std::string& filePath)
{
	std::ofstream file(filePath);

	file << m_fTrackWidth << " " << m_vPathPoints.size() << std::endl;

	for(NLib::NSize_t i = 0; i < m_vPathPoints.size(); ++i)
	{
		file << m_vPathPoints[i].x << " " << m_vPathPoints[i].y << std::endl;
	}
}

void Track::loadFromFile(const std::string& filePath)
{
	m_vPathPoints.clear();

	std::ifstream file(filePath);

	NLib::NSize_t uTrackSize;
	file >> m_fTrackWidth >> uTrackSize;

	m_vPathPoints.reserve(uTrackSize);

	while(file)
	{
		float x, y;
		file >> x;
		file >> y;

		if(file)
		{
			m_vPathPoints.push_back(NMVector2fLoad(x, y));
		}
	}
}

} // Simulation
