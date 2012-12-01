#ifndef SNN_GAME
#define SNN_GAME

#include <Box2D/Box2D.h>
#include <NLib/Base/nBase.hpp>
#include <SDL.h>
#include <memory>
#include <string>
#include <exception>

/**
 *
 */
struct GameSettings
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
class Image
	: NNonCopyable
{
public:
	Image(SDL_Surface* pSurface)
		: m_pSurface(pSurface)
	{}

	~Image()	{ SDL_FreeSurface(m_pSurface); }

	SDL_Surface* getSurface() const	{ return m_pSurface; }	// can't do const

private:
	SDL_Surface* m_pSurface;
};
typedef std::auto_ptr<Image> ImageAPtr;

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
class Game
{
public:
	Game(const GameSettings& settings);
	
	~Game();

	ImageAPtr createImage(const std::string& filePath) const;
	ImageAPtr createImage(const std::string& filePath, const RGBUint8& colorKey) const;

	void drawImage(NLib::NUint32 x, NLib::NUint32 y, Image& image) const;

	void flipScreen();

	bool update();

private:
	b2World m_b2World;

	SDL_Surface* m_pMainSurface;
	SDL_Event m_event;
};

#endif