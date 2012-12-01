#include "Game.hpp"
#include <SDL_image.h>
#include <SDL_opengl.h>


Game::Game(const GameSettings& settings)
    : m_b2World(b2Vec2(0.0f, 0.0f))
{
    SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_pMainSurface = SDL_SetVideoMode(settings.uWidth, 
                                    settings.uHeight, 
                                    settings.uBitsPerPixel, 
                                    SDL_OPENGL);
}

Game::~Game()
{
    SDL_FreeSurface(m_pMainSurface);
    SDL_Quit();
}

void Game::drawImage(NLib::NUint32 x, NLib::NUint32 y, Image& image) const
{
	SDL_Surface* pSrcSurface = image.getSurface();
	SDL_Rect dstRect = { x, y };

	SDL_BlitSurface(pSrcSurface, &pSrcSurface->clip_rect, m_pMainSurface, &dstRect);
}

void Game::flipScreen()
{
    SDL_Flip(m_pMainSurface);
}

ImageAPtr Game::createImage(const std::string& filePath) const
{
	RGBUint8 colorKey = {255,255,255};
	return createImage(filePath, colorKey);
}

ImageAPtr Game::createImage(const std::string& filePath, const RGBUint8& colorKey) const
{
	SDL_Surface* pImage = IMG_Load(filePath.c_str());

	if(pImage == null)
	{
		throw LoadFileException("Cannot load image from file: " + filePath);
	}

	// TODO: Actually supports only PNG with alpha
	SDL_Surface* pDisplayFormatSurface = pImage;
	//SDL_Surface* pDisplayFormatSurface = SDL_DisplayFormat(pImage);
	//SDL_FreeSurface(pImage);

	//if(pDisplayFormatSurface == null)
	//{
	//	throw LoadFileException("Cannot convert image to display format");
	//}

	//Uint32 uColorKey = SDL_MapRGB(pDisplayFormatSurface->format, colorKey.r, colorKey.g, colorKey.b);
	//SDL_SetColorKey(pDisplayFormatSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, uColorKey);

	return ImageAPtr(new Image(pDisplayFormatSurface));
}

bool Game::update()
{
    if(SDL_PollEvent(&m_event))
    {
        if(m_event.type == SDL_KEYDOWN)
        {
            if(m_event.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
        }
        else if(m_event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}
