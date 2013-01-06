#include "DifferentialEvolution.hpp"
#include <algorithm>
#include <set>
#include <limits>
#include <ctime>
#include <cstring>  // for memcpy
#include <fstream>

using namespace NLib;

namespace {

	const float DEFAULT_WEIGHT = 0.6f;
	const float DEFAULT_CR = 0.4f;

}

namespace DE {

DifferentialEvolution::DifferentialEvolution()
	: m_uIndividualSize(0)
	, m_uPopulationSize(0)
	, m_fWeight(DEFAULT_WEIGHT)
	, m_fCR(DEFAULT_CR)
	, m_uBestIndividual(0)
{
}

void DifferentialEvolution::loadGenerationFromFile(const std::string& filepath)
{
	std::ifstream in(filepath);

	for(NSize_t i = 0; i < m_aPopulations[0].size(); ++i)
	{
		in >> m_aPopulations[0][i];
	}
}

void DifferentialEvolution::setPopulationSize(NSize_t uSize)
{
	m_uPopulationSize = uSize;
	resizePopulations();

	m_costs.resize(uSize);
}

void DifferentialEvolution::setIndividualSize(NSize_t uSize)
{
	m_uIndividualSize = uSize;
	resizePopulations();
}

void DifferentialEvolution::resizePopulations()
{
	NSize_t uVectorSize = m_uIndividualSize * m_uPopulationSize;

	m_aPopulations[0].resize(uVectorSize);
	m_aPopulations[1].resize(uVectorSize);
}

void DifferentialEvolution::randomizeCurrentGeneration()
{
	std::default_random_engine generator(time(0));
	std::normal_distribution<float> distribution(0.0f, 1.0f);

	for(NSize_t i = 0; i < m_aPopulations[0].size(); ++i)
	{
		m_aPopulations[0].at(i) = distribution(generator);
	}

	m_uBestIndividual = 0;	// Reset of best individual
}

void DifferentialEvolution::prepareNextGeneration()
{
	std::set<NSize_t> m_distinctValues;

	for(NSize_t i = 0; i < m_uPopulationSize; ++i)
	{
		// Choosing 3 different values which differs also from i
		m_distinctValues.clear();
		m_distinctValues.insert(i);

		while(m_distinctValues.size() < 4)
		{
			m_distinctValues.insert(rand() % m_uPopulationSize);
		}

		// Getting 4 vectors from current generations
		SNN::real* pXi = getCurrentIndividualData(i);	// Target
		m_distinctValues.erase(i);

		SNN::real* pXc = getCurrentIndividualData(*m_distinctValues.begin());	// Xc
		m_distinctValues.erase(m_distinctValues.begin());

		SNN::real* pXa = getCurrentIndividualData(*m_distinctValues.begin());	// Xa
		m_distinctValues.erase(m_distinctValues.begin());

		SNN::real* pXb = getCurrentIndividualData(*m_distinctValues.begin());	// Xb
		m_distinctValues.erase(m_distinctValues.begin());

		// Place for next vector
		SNN::real* pXcNG = getNextIndividualData(i);	// individaul for calculations

		// mutation
		mutateIndividuals(pXcNG, pXa, pXb, pXc);

		// cross
		crossIndividuals(pXcNG, pXi);
	}
}

void DifferentialEvolution::mutateIndividuals(SNN::real* pDest, SNN::real* pXa, SNN::real* pXb, SNN::real* pXc)
{
	for(NSize_t i = 0; i < m_uIndividualSize; ++i)
	{
		pDest[i] = pXc[i] + m_fWeight * (pXa[i] - pXb[i]);
	}
}

void DifferentialEvolution::crossIndividuals(SNN::real* pDest, SNN::real* pXi)
{
	NSize_t uParameter = rand() % m_uIndividualSize;

	std::default_random_engine generator(time(0));
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	for(NSize_t i = 0; i < m_uIndividualSize; ++i)
	{
		float f = distribution(generator);

		if(i != uParameter && f >= m_fCR)
		{
			pDest[i] = pXi[i];
		}
	}
}

void DifferentialEvolution::updateIndividual(NLib::NSize_t uIndex, float fCost)
{
	if(fCost < m_costs[uIndex])
	{
		memcpy(getCurrentIndividualData(uIndex), getNextIndividualData(uIndex), sizeof(SNN::real) * m_uIndividualSize);
		m_costs[uIndex] = fCost;

		updateBestIndividual(uIndex, fCost);
	}
}

void DifferentialEvolution::updateBestIndividual(NSize_t uIndex, float fCost)
{
	if(fCost < m_costs[m_uBestIndividual])
	{
		m_uBestIndividual = uIndex;
	}
}

void DifferentialEvolution::setCost(NLib::NSize_t uIndex, float fCost)
{ 
	m_costs[uIndex] = fCost;
	updateBestIndividual(uIndex, fCost);
}

float DifferentialEvolution::getCost(NLib::NSize_t uIndex) const
{
	return m_costs[uIndex];
}

NLib::Math::NMVector2f DifferentialEvolution::getCostStats() const
{
	float fCostSum = 0.0f;

	for(NSize_t i = 0; i < m_costs.size(); ++i)
	{
		fCostSum += m_costs[i];
	}

	float fAverage = fCostSum / m_costs.size();

	fCostSum = 0.0f;

	for(NSize_t i = 0; i < m_costs.size(); ++i)
	{
		float fDiff = m_costs[i] - fAverage;
		fCostSum += fDiff * fDiff;
	}

	return NLib::Math::NMVector2fLoad(fAverage, fCostSum / m_costs.size());
}

} // DE
