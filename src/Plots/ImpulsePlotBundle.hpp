#ifndef SNN_PLOTS_IMPULSEPLOTBUNDLE
#define SNN_PLOTS_IMPULSEPLOTBUNDLE

#include <vector>
#include "Framework/Framework.hpp"
#include "ImpulsePlot.hpp"

namespace Plots {

class ImpulsePlotBundle
	: NLib::NNonCopyable
{
public:
	ImpulsePlotBundle(Framework::Framework& framework);
	~ImpulsePlotBundle();

	void update(float fDelta);

	void draw();

	ImpulsePlot&		createPlot(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size);
	void				addPlot(ImpulsePlotAPtr plot);

	ImpulsePlot&		getPlot(NLib::NSize_t uIndex)			{ return *m_plots[uIndex]; }
	const ImpulsePlot&	getPlot(NLib::NSize_t uIndex) const		{ return *m_plots[uIndex]; }

private:
	Framework::Framework& m_framework;
	std::vector<ImpulsePlot*> m_plots;
};

} // Plots

#endif // SNN_PLOTS_IMPULSEPLOTBUNDLE