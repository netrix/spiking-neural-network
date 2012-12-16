#include "Framework.hpp"
#include <SDL_image.h>

using namespace NLib::Math;

bool isPowOf2(NLib::NUint32 value)
{
    return (value & (value - 1)) == 0;
}


Framework::Framework(const FrameworkSettings& settings, float fWorldScale)
	: m_fDelta(0.0f)
	, m_uLastMouseButtonStateRight(0)
	, m_uLastMouseButtonStateLeft(0)
	, m_b2World(b2Vec2_zero)
	, m_bDrawDebug(false)
{
	// Window + Opengl
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
    glOrtho(0.0f, settings.uWidth * fWorldScale, settings.uHeight * fWorldScale, 0.0f, -1.0f, 1.0f);
	//glOrtho(-settings.uWidth*0.5f, settings.uWidth*0.5f, settings.uHeight*.5f, -settings.uHeight*0.5f, -1.0f, 1.0f);
 
	// Alpha blending
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Resetting events
	memset(&m_event, 0, sizeof(m_event));
	m_uLastMouseButtonStateLeft = SDL_MOUSEBUTTONUP;

	// Initializing physics
	m_b2World.SetDebugDraw(&m_b2DebugDrawOpenGL);

	uint32 flags = m_b2DebugDrawOpenGL.GetFlags();

	flags |= b2Draw::e_shapeBit;
	flags |= b2Draw::e_jointBit;
	flags |= b2Draw::e_aabbBit;
	flags |= b2Draw::e_centerOfMassBit;

	m_b2DebugDrawOpenGL.SetFlags(flags);

	// Time
	m_uTicks = SDL_GetTicks();
}

Framework::~Framework()
{
    SDL_FreeSurface(m_pMainSurface);
    SDL_Quit();
}

void Framework::drawSprite(float x, float y, float fAngle, Sprite& sprite) const
{
	NMVector2f size = sprite.getSize();
	NMVector2f offset = sprite.getOffset();

	float x1 = offset.x;
	float y1 = offset.y;
	float x2 = offset.x + size.x;
	float y2 = offset.y + size.y;

	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

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

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

void Framework::drawLine(NMVector2f pA, NMVector2f pB, Color3f color) const
{
	glBegin(GL_LINES);
	glColor3f(color.x, color.y, color.z);
    {
		glVertex2f(pA.x, pA.y);
		glVertex2f(pB.x, pB.y);
    }
    glEnd();
}

void Framework::drawArrow(NMVector2f origin, NMVector2f direction, Color3f color) const
{
	float fScale = 1.0f;
	direction = NMVector2fNormalize(direction);

	NMVector2f p2 = origin + direction * 4.0f * fScale;
	NMVector2f d1 = (p2 - direction) * fScale + NMVector2fLoad(-direction.y, direction.x) * fScale;
	NMVector2f d2 = (p2 - direction) * fScale + NMVector2fLoad(direction.y, -direction.x) * fScale;

	glBegin(GL_LINES);
	glColor3f(color.x, color.y, color.z);
    {
		glVertex2f(origin.x, origin.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(d1.x, d1.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(d2.x, d2.y);
		glVertex2f(p2.x, p2.y);
    }
    glEnd();
}

void Framework::drawLineStrip(const PointVector& vPoints, Color3f color) const
{
	glBegin(GL_LINE_STRIP);
	glColor3f(color.x, color.y, color.z);
    {
		for(NLib::NSize_t i = 0; i < vPoints.size(); ++i)
		{
			const NMVector2f& p = vPoints[i];
			glVertex2f(p.x, p.y);
		}
    }
    glEnd();
}

void Framework::drawTriangleStrip(const PointVector& vPoints, Color3f color) const
{
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(color.x, color.y, color.z, 0.5f);

	glBegin(GL_TRIANGLE_STRIP);
    {
		for(NLib::NSize_t i = 0; i < vPoints.size(); ++i)
		{
			const NMVector2f& p = vPoints[i];
			glVertex2f(p.x, p.y);
		}
    }
    glEnd();
	glDisable(GL_BLEND);
}

void Framework::drawRect(NLib::Math::NMVector2f origin, NLib::Math::NMVector2f size, Color4f color) const
{
	NLib::Math::NMVector2f p2 = origin + size;

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.x, 0.5f * color.y, 0.5f * color.z, color.w);
	glRectf(origin.x, origin.y, p2.x, p2.y);
	glDisable(GL_BLEND);
}

void Framework::flipScreen()
{
	if(m_bDrawDebug)
	{
		m_b2World.DrawDebugData();
	}

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
    NLib::NUint32 uColor3fNum = pSurface->format->BytesPerPixel;
    if(uColor3fNum == 4)
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

    glTexImage2D(GL_TEXTURE_2D, 0, uColor3fNum, pSurface->w, pSurface->h, 0, uTextureFormat, 
        GL_UNSIGNED_BYTE, pSurface->pixels);

    // Data from texture
	NMVector2f size = { pSurface->w, pSurface->h };

    SDL_FreeSurface(pSurface);

    return SpriteAPtr(new Sprite(uTexture, size));
}

bool Framework::update()
{
	// Time
	NLib::NUint32 uCurrentTics = SDL_GetTicks();
	m_fDelta = (float)(uCurrentTics - m_uTicks) / 1000.0f;
	m_uTicks = uCurrentTics;

	// Last state of left button
	if(m_event.button.button == SDL_BUTTON_LEFT)
	{
		m_uLastMouseButtonStateLeft = m_event.type;
	}
	if(m_event.button.button == SDL_BUTTON_RIGHT)
	{
		m_uLastMouseButtonStateRight = m_event.type;
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

NMVector2f Framework::getMouseCoords() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return NMVector2fLoad((float)x, (float)y);
}

bool Framework::isMouseButtonLeftClicked() const
{
	return m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_LEFT && m_uLastMouseButtonStateLeft != SDL_MOUSEBUTTONDOWN;
}

bool Framework::isMouseButtonRightClicked() const
{
	return m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_RIGHT && m_uLastMouseButtonStateRight != SDL_MOUSEBUTTONDOWN;
}

bool Framework::checkKeyDown(SDLKey key) const
{
	return SDL_GetKeyState(null)[key];
}

void Framework::setDebugDraw(bool value)
{
	m_bDrawDebug = value;
}

void Framework::physicsStep(float hz)
{
	float32 timeStep = hz > 0.0f ? 1.0f / hz : float32(0.0f);

	m_b2World.SetAllowSleeping(true);
	m_b2World.SetWarmStarting(true);
	m_b2World.SetContinuousPhysics(true);
	m_b2World.SetSubStepping(false);

	m_b2World.Step(timeStep, 8, 3);
}