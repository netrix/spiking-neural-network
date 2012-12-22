#ifndef SNN_PLOTS_IMPULSEPLOT
#define SNN_PLOTS_IMPULSEPLOT

#include "PlotRenderer.hpp"

namespace Plots {

class ImpulsePlot
	: NLib::NNonCopyable
{
public:
	ImpulsePlot(Framework::Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size);

	void addImpulse();

	void update(float fDelta);

	void draw();

	void setDrawScale(bool bValue)		{ m_oglPlot.setDrawScale(bValue); }

private:
	FloatVector m_impulses;
	NLib::Math::NMVector2f m_timeWindow;
	float m_fTime;

	PlotRenderer m_oglPlot;
};

} // Plots

#endif // SNN_PLOTS_IMPULSEPLOT