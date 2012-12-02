#include "Framework.hpp"
#include <SDL_image.h>

bool isPowOf2(NLib::NUint32 value)
{
    return (value & (value - 1)) == 0;
}


Framework::Framework(const FrameworkSettings& settings)
	: m_b2World(b2Vec2_zero)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_pMainSurface = SDL_SetVideoMode(settings.uWidth, 
                                    settings.uHeight, 
                                    settings.uBitsPerPixel, 
                                    SDL_OPENGL);

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
    glViewport(0, 0, settings.uWidth, settings.uHeight);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, settings.uWidth, settings.uHeight, 0.0f, -1.0f, 1.0f);
	//glOrtho(-settings.uWidth*0.5f, settings.uWidth*0.5f, settings.uHeight*.5f, -settings.uHeight*0.5f, -1.0f, 1.0f);
 
	// Alpha blending
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Resetting events
	memset(&m_event, 0, sizeof(m_event));
	m_uLastMouseButtonStateLeft = SDL_MOUSEBUTTONUP;

	// Initializing physics
	m_b2World.SetDebugDraw(&m_b2DebugDrawOpenGL);
}

Framework::~Framework()
{
    SDL_FreeSurface(m_pMainSurface);
    SDL_Quit();
}

void Framework::drawSprite(float x, float y, float fAngle, Sprite& sprite) const
{
	NLib::Math::NMVector2f size = sprite.getSize();
	NLib::Math::NMVector2f offset = sprite.getOffset();

	float x1 = offset.x;
	float y1 = offset.y;
	float x2 = offset.x + size.x;
	float y2 = offset.y + size.y;

	glMatrixMode(GL_MODELVIEW);

    // Rotation
	glTranslatef((float)x, (float)y, 0.0f);
    glRotatef((float)fAngle, 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, sprite.getTexture());
    glBegin(GL_QUADS);
    {
        //Bottom-left vertex (corner)
        glTexCoord2i(0, 0);
        glVertex3f(x1, y1, 0.0f);
 
        //Bottom-right vertex (corner)
        glTexCoord2i(1, 0);
        glVertex3f(x2, y1, 0.f);
 
        //Top-right vertex (corner)
        glTexCoord2i(1, 1);
        glVertex3f(x2, y2, 0.f);
 
        //Top-left vertex (corner)
        glTexCoord2i(0, 1);
        glVertex3f(x1, y2, 0.f);
    }
    glEnd();

    glLoadIdentity();
}

void Framework::flipScreen()
{
    SDL_GL_SwapBuffers();

    glClear(GL_COLOR_BUFFER_BIT);
}

SpriteAPtr Framework::createSprite(const std::string& filePath) const
{
    SDL_Surface* pSurface = IMG_Load(filePath.c_str());

    if(pSurface == null)
    {
        throw LoadFileException("Cannot load sprite from file: " + filePath);
    }

    if(!isPowOf2(pSurface->w) || !isPowOf2(pSurface->h))
    {
        throw LoadFileException("Loaded file's dimensions are not power of 2");
    }

    // Checking alpha channel
    GLenum uTextureFormat;
    NLib::NUint32 uColorNum = pSurface->format->BytesPerPixel;
    if(uColorNum == 4)
    {
        if(pSurface->format->Rmask == 0x000000ff)
        {
            uTextureFormat = GL_RGBA;
        }
        else
        {
            uTextureFormat = GL_BGRA;
        }
    }

    // Creating GL texture
    GLenum uTexture;
    glGenTextures(1, &uTexture);
    glBindTexture(GL_TEXTURE_2D, uTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, uColorNum, pSurface->w, pSurface->h, 0, uTextureFormat, 
        GL_UNSIGNED_BYTE, pSurface->pixels);

    // Data from texture
	NLib::Math::NMVector2f size = { pSurface->w, pSurface->h };

    SDL_FreeSurface(pSurface);

    return SpriteAPtr(new Sprite(uTexture, size));
}

bool Framework::update()
{
	// Last state of left button
	if(m_event.button.button == SDL_BUTTON_LEFT)
	{
		m_uLastMouseButtonStateLeft = m_event.type;
	}

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

NLib::Math::NMVector2f Framework::getMouseCoords() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return NLib::Math::NMVector2fLoad((float)x, (float)y);
}

bool Framework::isMouseButtonLeftClicked() const
{
	return m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_LEFT && m_uLastMouseButtonStateLeft != SDL_MOUSEBUTTONDOWN;
}

bool Framework::checkKeyDown(SDLKey key) const
{
	return m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == key;
}

void Framework::setDebugDraw(bool value)
{
	if(value)
	{
		uint32 flags = m_b2DebugDrawOpenGL.GetFlags();

		flags |= b2Draw::e_shapeBit;
		flags |= b2Draw::e_jointBit;
		flags |= b2Draw::e_aabbBit;
		flags |= b2Draw::e_centerOfMassBit;

		m_b2DebugDrawOpenGL.SetFlags(flags);
	}
	else
	{
		uint32 flags = m_b2DebugDrawOpenGL.GetFlags();

		flags &= ~b2Draw::e_shapeBit;
		flags &= ~b2Draw::e_jointBit;
		flags &= ~b2Draw::e_aabbBit;
		flags &= ~b2Draw::e_centerOfMassBit;

		m_b2DebugDrawOpenGL.SetFlags(flags);
	}
}