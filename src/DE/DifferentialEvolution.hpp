#ifndef SNN_DE_SOURCES
#define SNN_DE_SOURCES

#include <NLib/Base/nBase.hpp>
#include <NLib/Base/nNonCopyable.hpp>
#include <NLib/Math/nMath.hpp>
#include <random>
#include <vector>
#include "SNN/Common.hpp"

namespace DE {

class DifferentialEvolution
	: NLib::NNonCopyable
{
	typedef std::vector<SNN::real> RealVector;
	typedef std::vector<float> FloatVector;

public:
	DifferentialEvolution();

	void saveGenerationToFile(const std::string& filepath);
	void loadGenerationFromFile(const std::string& filepath);

	void			setPopulationSize(NLib::NSize_t uSize);
	NLib::NSize_t	getPopulationSize() const						{ return m_uPopulationSize; }

	void			setIndividualSize(NLib::NSize_t uSize);
	NLib::NSize_t	getIndividualSize() const						{ return m_uIndividualSize; }

	void			setWeight(float fWeight)		{ m_fWeight = fWeight; }
	float			getWeight() const				{ return m_fWeight; }

	void			setCR(float fCR)				{ m_fCR = fCR; }
	float			getCR() const					{ return m_fCR; }

	void randomizeCurrentGeneration();

	void prepareNextGeneration();

	/** \brief Updates current individual by cost.
	 *  If new cost is smaller than previous cost of an individual, 
	 *  individual is swapped with next gen version.
	 *
	 *  \param uIndex Index of individual.
	 *  \param fCost Cost of individual of next generation.
	 */
	void updateIndividual(NLib::NSize_t uIndex, float fCost);

	void					setCost(NLib::NSize_t uIndex, float fCost);
	float					getCost(NLib::NSize_t uIndex) const;
	NLib::Math::NMVector2f	getCostStats() const;

	const SNN::real*	getCurrentIndividualData(NLib::NSize_t uIndex) const	{ return &m_aPopulations[0].at(m_uIndividualSize * uIndex); }
	SNN::real*			getCurrentIndividualData(NLib::NSize_t uIndex)			{ return &m_aPopulations[0].at(m_uIndividualSize * uIndex); }

	const SNN::real*	getNextIndividualData(NLib::NSize_t uIndex) const	{ return &m_aPopulations[1].at(m_uIndividualSize * uIndex); }
	SNN::real*			getNextIndividualData(NLib::NSize_t uIndex)			{ return &m_aPopulations[1].at(m_uIndividualSize * uIndex); }

	float				getBestCost() const				{ return m_costs[m_uBestIndividual]; }
	const SNN::real*	getBestIndividual() const		{ return getCurrentIndividualData(m_uBestIndividual); }
	NLib::NSize_t		getBestIndividualIndex() const	{ return m_uBestIndividual; }

private:
	void resizePopulations();

	void mutateIndividuals(SNN::real* pDest, SNN::real* pXa, SNN::real* pXb, SNN::real* pXc);

	void crossIndividuals(SNN::real* pDest, SNN::real* pXi);

	void updateBestIndividual(NLib::NSize_t uIndex, float fCost);

private:
	RealVector m_aPopulations[2];
	FloatVector m_costs;			// Cost for individuals of current generation

	NLib::NSize_t m_uIndividualSize;
	NLib::NSize_t m_uPopulationSize;
	float m_fWeight;
	float m_fCR;

	NLib::NSize_t m_uBestIndividual;
};

} // DE

#endif // SNN_SNN_SPIKINGNEURON
