#ifndef SNN_IAPPLICATIONCONTROLLER
#define SNN_IAPPLICATIONCONTROLLER

class IApplicationController
{
public:
	virtual void initController() = 0;

	virtual bool handleKeys() = 0;

	virtual void fixedStepUpdate() = 0;
};

#endif // SNN_IAPPLICATIONSTATE