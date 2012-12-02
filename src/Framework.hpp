#ifndef SNN_GAME
#define SNN_GAME

#include <NLib/Base/nBase.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include <string>
#include <Box2D/Box2D.h>

#include "Exceptions.hpp"
#include "DebugDrawOpenGL.hpp"
#include "Sprite.hpp"

typedef std::auto_ptr<Sprite> SpriteAPtr;

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
	Framework(const FrameworkSettings& settings);
	~Framework();

	// Graphics
	SpriteAPtr createSprite(const std::string& filePath) const;
	void drawSprite(float x, float y, float fAngle, Sprite& sprite) const;
	void flipScreen();

	// Events
	bool update();
	NLib::Math::NMVector2f getMouseCoords() const;
	bool isMouseButtonLeftClicked() const;
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

	// Box2D
	b2World m_b2World;

	// Debug
	DebugDrawOpenGL m_b2DebugDrawOpenGL;
};

#endif