#ifndef SNN_TRACK
#define SNN_TRACK

#include <vector>
#include <NLib/Math/nMath.hpp>

typedef std::vector<NLib::Math::NMVector2f> PointVector;

class Track
{
public:
	Track();

	void addPoint(const NLib::Math::NMVector2f& point);

	NLib::NSize_t getSize() const;

	const NLib::Math::NMVector2f& getPoint(NLib::NSize_t uIndex) const;

	const NLib::Math::NMVector2f& last() const;

	void clear();

	void setTrackWidth(float fTrackWidth);

	float getTrackWidth() const;

	float getTrackLength() const;

	void setCurrentPosition(const NLib::Math::NMVector2f& point);

	float getCurrentDistance() const;

	const PointVector& getTrackLineStripPoints() const;

	PointVector getTrackTriangleStripPoints() const;

private:
	PointVector m_vPathPoints;
	NLib::NSize_t m_uCurrentPoint;
	NLib::Math::NMVector2f m_uCurrentPosition;
	float m_fTrackWidth;
};

#endif // SNN_TRACK