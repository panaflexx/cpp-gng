#include "base.h"
#include "Renderer.h"

#include <cassert>

#include "Entity.h"
#include "Texture.h"
#include "Transform.h"

Renderer::Renderer(Entity* pParent, Texture* pTexture)
	: Component(pParent)
	, m_pTexture{ pTexture }
{
}

void Renderer::Initialize()
{
	m_pParentTransform = m_pParent->GetComponent<Transform>();
	assert(m_pParentTransform != nullptr && "Entity has renderer component but not transform component");
}

void Renderer::Draw() const
{
	glTranslatef(m_pParentTransform->GetPosition().x, m_pParentTransform->GetPosition().y, 0);

	const float renderScale = m_pParentTransform->GetScale();
	glScalef(
		m_FlipX ? -renderScale : renderScale,
		m_FlipY ? -renderScale : renderScale,
		0
	);

	// Make renderer generic by abstracting this into virtual function
	m_pTexture->Draw(Rectf(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight()));

}

bool Renderer::GetFlipX() const
{
	return m_FlipX;
}

void Renderer::SetFlipX(bool newState)
{
	m_FlipX = newState;
}

bool Renderer::GetFlipY() const
{
	return m_FlipY;
}

void Renderer::SetFlipY(bool newState)
{
	m_FlipY = newState;
}
