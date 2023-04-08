#include "base.h"
#include "PartialRenderer.h"

#include "Texture.h"

PartialRenderer::PartialRenderer(Entity* pParent, Texture* pTexture, int spriteAmount, int startIndex, bool horizontal)
	: Renderer(pParent, pTexture)
	, m_Horizontal{ horizontal }
	, m_SpriteAmount{ spriteAmount }
	, m_Index{ startIndex }
{
}

void PartialRenderer::DrawSprite() const
{
	const float mainAxisTextureSize{ m_Horizontal ? m_pTexture->GetWidth() : m_pTexture->GetHeight() };
	const float mainAxisSpriteSize{ mainAxisTextureSize / static_cast<float>(m_SpriteAmount) };

	Rectf src;
	if (m_Horizontal) src = Rectf(static_cast<float>(m_Index) * mainAxisSpriteSize, 0, mainAxisSpriteSize, m_pTexture->GetHeight());
	else              src = Rectf(0, static_cast<float>(m_Index) * mainAxisSpriteSize, m_pTexture->GetWidth(), mainAxisSpriteSize);

	m_pTexture->DrawCentered(src);
}
