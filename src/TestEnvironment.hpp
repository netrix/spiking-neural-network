#ifndef SNN_TEST_ENVIRONMENT
#define SNN_TEST_ENVIRONMENT

#include <vector>
#include <NLib/Base/nBase.hpp>
#include "Common.hpp"

struct TimeReaction
{
	std::vector<real> inputs;
	bool impulse;
};

class TestEnvironment
{
public:
	TimeReaction& getTimeReactionAtTime(NLib::NSize_t uTime);

private:
	std::vector<TimeReaction> m_aTimeReaction;
};

#endif // SNN_TEST_ENVIRONMENT

inline TimeReaction& TestEnvironment::getTimeReactionAtTime(NLib::NSize_t uTime)
{
	if(uTime > m_aTimeReaction.size())
	{
		m_aTimeReaction.resize(uTime + 1);
	}

	return m_aTimeReaction[uTime];
}