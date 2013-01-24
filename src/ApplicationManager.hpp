#ifndef SNN_APPLICATIONMANAGER
#define SNN_APPLICATIONMANAGER

#include <array>
#include <NLib/Base/nNonCopyable.hpp>
#include "Plots/ImpulsePlotBundle.hpp"
#include "Plots/LinePlot.hpp"
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"
#include "SNN/SpikingNetwork.hpp"
#include "NeuronImpulseHandler.hpp"

#include "IApplicationController.hpp"
#include "UserController.hpp"
#include "NeuralNetworkController.hpp"

class ApplicationManager
	: public IApplicationController
	, NLib::NNonCopyable
{
	static const NLib::NSize_t NEURON_INPUT_COUNT = 7;

public:
	ApplicationManager();
	~ApplicationManager();

	void run();

private:
	void initSprites();
	void initSpikingNetwork();
	void initPlots();
	void initWorld();

	void draw();
	bool handleApplicationKeys();

	virtual void initController();
	virtual bool handleKeys();
	virtual void fixedStepUpdate();

	void setApplicationController(IApplicationController& pController);

	void setCurrentLinePlot(NLib::NSize_t uPlotIndex);

private:
	Framework::Framework		m_framework;
	const float					m_fWorldScale;
	IApplicationController*		m_pApplicationController;

	Framework::SpriteAPtr		m_carSprite;
	Framework::SpriteAPtr		m_backgroundSprite;

	bool						m_bShowPlots;
	std::string					m_currentTrackPath;
	NLib::NSize_t				m_uCurrentLinePlot;

	Plots::ImpulsePlotBundle	m_impulsePlotBundle;
	Plots::LinePlot				m_linePlot;
	Simulation::World			m_testWorld;
	SNN::SpikingNetwork			m_spikingNetwork;
	
	std::array<NeuronImpulseHandler*, NEURON_INPUT_COUNT> m_aNeuronImpulseHandlers;

	UserController				m_userController;
	NeuralNetworkController		m_networkController;
};

#endif // SNN_APPLICATIONMANAGER