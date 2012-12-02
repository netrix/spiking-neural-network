#ifndef SNN_GAME
#define SNN_GAME

#include <NLib/Base/nBase.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <memory>
#include <string>
#include <exception>

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
class NNonCopyable
{
protected:
	NNonCopyable() {}
	~NNonCopyable() {}

private:
	NNonCopyable(const NNonCopyable&) {}
	const NNonCopyable& operator=(const NNonCopyable&) {}
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
class Sprite
	: NNonCopyable
{
public:
	Sprite(GLuint uTexture, const NLib::Math::NMVector2f& size)
		: m_uTexture(uTexture)
		, m_offset(NLib::Math::NMVector2fLoadZeros())
		, m_size(size)

	{}

	~Sprite()	{  glDeleteTextures(1, &m_uTexture); }

	GLuint getTexture() const { return m_uTexture; }

	const NLib::Math::NMVector2f& getSize() const { return m_size; }

	void setSize(const NLib::Math::NMVector2f& size)	{ m_size = size; }

	void setOffset(const NLib::Math::NMVector2f& offset)	{ m_offset = offset; }

	const NLib::Math::NMVector2f& getOffset() const { return m_offset; }

private:
	GLuint m_uTexture;
	NLib::Math::NMVector2f m_offset;
	NLib::Math::NMVector2f m_size;
};
typedef std::auto_ptr<Sprite> SpriteAPtr;

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

/**
 *
 */
class Framework
{
public:
	Framework(const FrameworkSettings& settings);
	
	~Framework();

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
};

#endif