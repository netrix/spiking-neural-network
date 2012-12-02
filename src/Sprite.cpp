#include "Sprite.hpp"

Sprite::Sprite(GLuint uTexture, const NLib::Math::NMVector2f& size)
	: m_uTexture(uTexture)
	, m_offset(NLib::Math::NMVector2fLoadZeros())
	, m_size(size)

{}