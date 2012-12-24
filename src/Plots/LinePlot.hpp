#ifndef SNN_PLOTS_LINEPLOT
#define SNN_PLOTS_LINEPLOT

#include <memory>
#include "PlotRenderer.hpp"

namespace Plots {

class LinePlot
	: NLib::NNonCopyable
{
public:
	// Ten wykres bedzie przyjmowal stala liczbe wartosci na zasadzie kolejki FIFO, nowa wrzucona wartosc bedzie usuwala ostatnia w przypadku przepelnienia
	// Kontener bedzie cykliczny, bedzie wyswietlal wszystko, trzeba to podpiac pod neuron i zobaczyc co tam jest w srodku
	LinePlot(Framework::Framework& framework, const NLib::Math::NMVector2f& position, const NLib::Math::NMVector2f& size, NLib::NSize_t uMaxSize);
	
	virtual ~LinePlot()	{}

	void pushValue(float fValue);

	void draw();

	void setDrawScale(bool bValue)		{ m_oglPlot.setDrawScale(bValue); }

private:
	NLib::Math::NMVector2f m_minMax;
	FloatVector m_values;

	PlotRenderer m_oglPlot;
};

typedef std::auto_ptr<LinePlot> LinePlotAPtr;

} // Plots

#endif // SNN_PLOTS_LINEPLOT