#ifndef SNN_IMPULSE_PLOT
#define SNN_IMPULSE_PLOT

#include "PlotOpenGL.hpp"

class ImpulsePlot
	: NLib::NNonCopyable
{
public:
	ImpulsePlot(Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size);

	void addImpulse();

	void update(float fDelta);

	void draw();

	void setDrawScale(bool bValue)		{ m_oglPlot.setDrawScale(bValue); }

private:
	FloatVector m_impulses;
	NLib::Math::NMVector2f m_timeWindow;
	float m_fTime;

	PlotOpenGL m_oglPlot;
};

#endif // SNN_IMPULSE_PLOT