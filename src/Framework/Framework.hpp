#ifndef SNN_FRAMEWORK_FRAMEWORK
#define SNN_FRAMEWORK_FRAMEWORK

#include <NLib/Base/nBase.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "DebugDrawOpenGL.hpp"
#include "Sprite.hpp"

namespace Framework {

typedef std::auto_ptr<Sprite> SpriteAPtr;
typedef std::vector<NLib::Math::NMVector2f> PointVector;
typedef NLib::Math::NMVector3f Color3f;
typedef NLib::Math::NMVector4f Color4f;

/**
 *
 */
struct FrameworkSettings
{
	NLib::NUint16 uWidth;
	NLib::NUint16 uHeight;
	NLib::NUint16 uBitsPerPixel;
};

/**
 *
 */
class Framework
{
public:
	Framework(const FrameworkSettings& settings, float fWorldScale);
	~Framework();

	// Time
	float getTimeDelta() const	{ return m_fDelta; }

	// Graphics
	SpriteAPtr createSprite(const std::string& filePath) const;
	void drawSprite(float x, float y, float fAngle, Sprite& sprite) const;
	void drawLine(NLib::Math::NMVector2f pA, NLib::Math::NMVector2f pB, Color3f color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawArrow(NLib::Math::NMVector2f origin, NLib::Math::NMVector2f direction, Color3f color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawLineStrip(const PointVector& vPoints, Color3f color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawTriangleStrip(const PointVector& vPoints, Color3f color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawRect(NLib::Math::NMVector2f origin, NLib::Math::NMVector2f size, Color4f color=NLib::Math::NMVector4fLoad(1.0f, 1.0f, 1.0f, 1.0f)) const;
	void flipScreen();

	// Events
	bool update();
	NLib::Math::NMVector2f getMouseCoords() const;
	bool isMouseButtonLeftClicked() const;
	bool isMouseButtonRightClicked() const;
	bool checkKeyDown(SDLKey key) const;

	// Debug
	void setDebugDraw(bool value);
	const b2Draw& getDebugDraw() const			{ return m_b2DebugDrawOpenGL; }

private:
	// SDL
	SDL_Surface* m_pMainSurface;
	SDL_Event m_event;
	
	// Time
	NLib::NUint32 m_uTicks;
	float m_fDelta;

	// Events
	NLib::NUint8 m_uLastMouseButtonStateLeft;
	NLib::NUint8 m_uLastMouseButtonStateRight;

	// Debug
	DebugDrawOpenGL m_b2DebugDrawOpenGL;
};

} // Framework

#endif // SNN_FRAMEWORK_FRAMEWORK