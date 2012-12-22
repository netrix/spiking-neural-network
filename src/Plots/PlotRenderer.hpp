#ifndef SNN_PLOTS_PLOT_RENDERER
#define SNN_PLOTS_PLOT_RENDERER

#include "Framework/Framework.hpp"

namespace Plots {

typedef std::vector<float> FloatVector;

class PlotRenderer
	: NLib::NNonCopyable
{
public:
	PlotRenderer(const Framework::Framework& fw);

	void setPosition(const NLib::Math::NMVector2f& position)	{ m_position = position; m_bNeedRecalculation = true; }
	void setSize(const NLib::Math::NMVector2f& size)			{ m_size = size; m_bNeedRecalculation = true; }
	void setMargins(NLib::Math::NMVector4f margins)				{ m_margins = margins; m_bNeedRecalculation = true; }

	void setDrawScale(bool bDrawScale)							{ m_bDrawScale = bDrawScale; m_bNeedRecalculation = true; }

	void drawImpulses(const FloatVector& times, const NLib::Math::NMVector2f& timeWindow);

private:
	void drawBasics();

	void drawArrowhead(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& direction);
	void drawScale(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, int uScale);
	void drawScaleStep(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, float fStep);

	void calculateBasics();

private:
	const Framework::Framework& m_framework;
	NLib::Math::NMVector2f m_position;
	NLib::Math::NMVector2f m_size;
	NLib::Math::NMVector4f m_margins;	// top, right, bottom, left

	bool m_bDrawScale;
	bool m_bNeedRecalculation;

	NLib::Math::NMVector2f m_xAxisA, m_xAxisB;
	NLib::Math::NMVector2f m_yAxisA, m_yAxisB;
	float m_fScaleLengthX;
	float m_fScaleLengthY;
};

} // Plots

#endif // SNN_PLOTS_PLOT_RENDERER