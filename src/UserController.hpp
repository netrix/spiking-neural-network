#ifndef SNN_USERCONTROLLER
#define SNN_USERCONTROLLER

#include <NLib/Base/nNonCopyable.hpp>
#include "Framework/Framework.hpp"
#include "Simulation/World.hpp"
#include "IApplicationController.hpp"

class UserController
	: public IApplicationController
	, NLib::NNonCopyable
{
public:
	UserController(Framework::Framework& framework, Simulation::World& world);

	virtual void initController();
	virtual bool handleKeys();
	virtual void fixedStepUpdate();

private:
	Framework::Framework& m_framework;
	Simulation::World& m_world;
};

#endif // SNN_USERCONTROLLER