#ifndef SNN_PLOT_OPENGL
#define SNN_PLOT_OPENGL

#include "Framework.hpp"

class PlotOpenGL
	: NLib::NNonCopyable
{
public:
	PlotOpenGL(const Framework& fw);

	void setPosition(const NLib::Math::NMVector2f& position)	{ m_position = position; }
	void setSize(const NLib::Math::NMVector2f& size)			{ m_size = size; }
	void setMargins(NLib::Math::NMVector4f margins)				{ m_margins = margins; }

	void drawBasics();

private:
	void drawArrowhead(const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& direction);
	void drawScale(const NLib::Math::NMVector2f& p1, const NLib::Math::NMVector2f& p2, NLib::NSize_t uScale);

private:
	const Framework& m_framework;
	NLib::Math::NMVector2f m_position;
	NLib::Math::NMVector2f m_size;
	NLib::Math::NMVector4f m_margins;	// top, right, bottom, left
};

#endif // SNN_PLOT_OPENGL