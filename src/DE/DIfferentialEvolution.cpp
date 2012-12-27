#include "DifferentialEvolution.hpp"
#include <algorithm>

using namespace NLib;

namespace DE {

DifferentialEvolution::DifferentialEvolution()
	: m_uIndividualSize(0)
	, m_uPopulationSize(0)
{
}

void DifferentialEvolution::setPopulationSize(NSize_t uSize)
{
	/*m_population.resize(uSize);

	std::for_each(m_population.begin(), m_population.end(), [=](RealVector& individual)
	{
		individual.resize(m_uIndividualSize);
	});*/
}

} // DE