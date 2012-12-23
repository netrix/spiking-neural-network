#ifndef SNN_PLOTS_IMPULSEPLOT
#define SNN_PLOTS_IMPULSEPLOT

#include <memory>
#include "PlotRenderer.hpp"

namespace Plots {

class ImpulsePlot
	: NLib::NNonCopyable
{
public:
	ImpulsePlot(Framework::Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size);
	
	virtual ~ImpulsePlot()	{}

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

typedef std::auto_ptr<ImpulsePlot> ImpulsePlotAPtr;

} // Plots

#endif // SNN_PLOTS_IMPULSEPLOT