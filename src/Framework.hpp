#ifndef SNN_GAME
#define SNN_GAME

#include <NLib/Base/nBase.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include <string>
#include <exception>

#include "DebugDrawOpenGL.hpp"
#include "Sprite.hpp"

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
struct RGBUint8
{
	NLib::NUint8 r, g, b;
};

/**
 *
 */
struct NSize
{
	NLib::NUint32 width;
	NLib::NUint32 height;
};


/**
 *
 */
class LoadFileException
	: public std::runtime_error
{
public:
	LoadFileException(const std::string& message)
		: runtime_error(message)
	{}
};

typedef std::auto_ptr<Sprite> SpriteAPtr;

/**
 *
 */
class Framework
{
public:
	Framework(const FrameworkSettings& settings);
	
	~Framework();

	b2Draw& getB2DebugDraw()		{ return m_b2DebugDrawOpenGL; }

	SpriteAPtr createSprite(const std::string& filePath) const;

	void drawSprite(float x, float y, float fAngle, Sprite& sprite) const;

	void flipScreen();

	bool update();

	NLib::Math::NMVector2f getMouseCoords() const;

	bool isMouseButtonLeftClicked() const;

	bool checkKeyDown(SDLKey key) const;

private:
	SDL_Surface* m_pMainSurface;
	SDL_Event m_event;

	NLib::NUint8 m_uLastMouseButtonStateLeft;

	DebugDrawOpenGL m_b2DebugDrawOpenGL;
};

#endif