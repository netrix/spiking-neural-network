#ifndef SNN_DE_SOURCES
#define SNN_DE_SOURCES

#include <NLib/Base/nBase.hpp>
#include <NLib/Base/nNonCopyable.hpp>
#include <vector>
#include "SNN/Common.hpp"

namespace DE {

class DifferentialEvolution
	: NLib::NNonCopyable
{
	typedef std::vector<SNN::real> RealVector;

public:
	DifferentialEvolution();

	void			setPopulationSize(NLib::NSize_t uSize);
	NLib::NSize_t	getPopulationSize() const						{ return m_population.size(); }

	void			setIndividualSize(NLib::NSize_t uSize);
	NLib::NSize_t	getIndividualSize() const						{ return m_uIndividualSize; }

	void calculateNextGeneration();

	const SNN::real*	getIndividualData(NLib::NSize_t uIndex) const	{ return &m_population[uIndex][0]; }
	SNN::real*	getIndividualData(NLib::NSize_t uIndex)					{ return &m_population[uIndex][0]; }

private:
	std::vector<RealVector> m_population;
	NLib::NSize_t m_uIndividualSize;
};

} // DE

#endif // SNN_SNN_SPIKINGNEURON
