#include "pch.h"
#include "LevelScene.h"

#include "Camera.h"
#include "Entity.h"

#include "EntityKeeper.h"
#include "Renderer.h"
#include "TextureCache.h"
#include "Transform.h"

LevelScene::LevelScene()
	: Scene(new Camera(10.f))
{
}

void LevelScene::InitializeScene()
{
	m_pTextureCache->LoadTexture("pengo", "pengo.png");
	m_pPlayer = m_pEntityKeeper->CreateEntity();
	m_pPlayer->AddComponent(new Transform(m_pPlayer));
	m_pPlayer->GetComponent<Transform>()->SetPosition(Vector2f(20, 20));
	m_pPlayer->AddComponent(new Renderer(m_pPlayer, m_pTextureCache->GetTexture("pengo")));

	m_pPlayer->Initialize();
}

void LevelScene::UpdateScene(float deltaTime)
{
}

void LevelScene::DrawScene() const
{
}
