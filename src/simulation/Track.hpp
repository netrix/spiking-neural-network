#ifndef SNN_SIMULATION_TRACK
#define SNN_SIMULATION_TRACK

#include <vector>
#include <NLib/Math/nMath.hpp>

namespace Simulation {

typedef std::vector<NLib::Math::NMVector2f> PointVector;

class Track
{
public:
	Track();

	void addPoint(const NLib::Math::NMVector2f& point);
	void popPoint();

	void movePoint(NLib::NSize_t uIndex, const NLib::Math::NMVector2f& point);

	NLib::NSize_t getSize() const;

	const NLib::Math::NMVector2f& getPoint(NLib::NSize_t uIndex) const;
	const NLib::Math::NMVector2f& getLastPoint() const;

	void	clear();

	void	setTrackWidth(float fTrackWidth);
	float	getTrackWidth() const;

	float	getTrackLength() const;

	void							setCurrentPosition(const NLib::Math::NMVector2f& point);
	const NLib::Math::NMVector2f&	getCurrentPosition() const		{ return m_currentPosition; }

	float getCurrentDistanceFromTrack() const;
	float getCurrentSideFromTrack() const;
	float getTravelledDistance() const;

	const NLib::Math::NMVector2f& getCurrentPointOnTrack() const;
	NLib::Math::NMVector2f getDirectionOfTrack() const;
	
	bool isAtStart() const;
	bool isAtEnd() const;

	const PointVector&	getTrackLineStripPoints() const;
	PointVector			getTrackTriangleStripPoints() const;

	void saveToFile(const std::string& filePath);
	void loadFromFile(const std::string& filePath);

private:
	NLib::NSize_t findClosestPoint(const NLib::Math::NMVector2f& point);

	NLib::NSize_t findClosestPointAround(NLib::NSize_t uIndex, const NLib::Math::NMVector2f& point);

private:
	PointVector m_vPathPoints;
	NLib::NSize_t m_uCurrentPoint;
	NLib::Math::NMVector2f m_currentPointOnTrack;
	NLib::Math::NMVector2f m_currentPosition;
	bool m_bIsPointCloser;
	float m_fTrackWidth;
};

} // Simulation

#endif // SNN_SIMULATION_TRACK