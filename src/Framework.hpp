#ifndef SNN_GAME
#define SNN_GAME

#include <NLib/Base/nBase.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include <string>
#include <vector>
#include <Box2D/Box2D.h>

#include "Exceptions.hpp"
#include "DebugDrawOpenGL.hpp"
#include "Sprite.hpp"

typedef std::auto_ptr<Sprite> SpriteAPtr;
typedef std::vector<NLib::Math::NMVector2f> PointVector;
typedef NLib::Math::NMVector3f Color;

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

	// Graphics
	SpriteAPtr createSprite(const std::string& filePath) const;
	void drawSprite(float x, float y, float fAngle, Sprite& sprite) const;
	void drawLine(NLib::Math::NMVector2f pA, NLib::Math::NMVector2f pB, Color color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawArrow(NLib::Math::NMVector2f origin, NLib::Math::NMVector2f direction, Color color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawLineStrip(const PointVector& vPoints, Color color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void drawTriangleStrip(const PointVector& vPoints, Color color=NLib::Math::NMVector3fLoad(1.0f, 1.0f, 1.0f)) const;
	void flipScreen();

	// Events
	bool update();
	NLib::Math::NMVector2f getMouseCoords() const;
	bool isMouseButtonLeftClicked() const;
	bool isMouseButtonRightClicked() const;
	bool checkKeyDown(SDLKey key) const;

	// Physics
	b2World& getPhysicsWorld()		{ return m_b2World; }
	void physicsStep(float hz);

	// Debug
	void setDebugDraw(bool value);

private:
	// SDL
	SDL_Surface* m_pMainSurface;
	SDL_Event m_event;
	

	// Events
	NLib::NUint8 m_uLastMouseButtonStateLeft;
	NLib::NUint8 m_uLastMouseButtonStateRight;

	// Box2D
	b2World m_b2World;

	// Debug
	bool m_bDrawDebug;
	DebugDrawOpenGL m_b2DebugDrawOpenGL;
};

#endif