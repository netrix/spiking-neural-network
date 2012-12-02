#ifndef SNN_SPRITE
#define SNN_SPRITE

#include <NLib/Base/nNonCopyable.hpp>
#include <NLib/Math/nMath.hpp>
#include <SDL_opengl.h>

/**
 *
 */
class Sprite
	: NLib::NNonCopyable
{
public:
	Sprite(GLuint uTexture, const NLib::Math::NMVector2f& size);

	~Sprite()												{  glDeleteTextures(1, &m_uTexture); }

	GLuint getTexture() const								{ return m_uTexture; }

	void setSize(const NLib::Math::NMVector2f& size)		{ m_size = size; }

	const NLib::Math::NMVector2f& getSize() const			{ return m_size; }

	void setOffset(const NLib::Math::NMVector2f& offset)	{ m_offset = offset; }

	const NLib::Math::NMVector2f& getOffset() const			{ return m_offset; }

private:
	GLuint m_uTexture;
	NLib::Math::NMVector2f m_offset;
	NLib::Math::NMVector2f m_size;
};

#endif // SNN_SPRITE