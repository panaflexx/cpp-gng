// ReSharper disable once CppUnusedIncludeDirective, This is pch
#include "base.h"
#include "Scene.h"

#include <cassert>

#include "Camera.h"
#include "EntityKeeper.h"
#include "TextureCache.h"

Scene::Scene(Camera* pCamera)
	: m_pGame{ nullptr }
	, m_pEntityKeeper{ new EntityKeeper(this) }
	, m_pTextureCache{ new TextureCache() }
	, m_pCamera{ pCamera }
{
}

Scene::~Scene()
{
	delete m_pEntityKeeper;
	delete m_pTextureCache;
	delete m_pCamera;
}

void Scene::Initialize(Game* pGame)
{
	m_pGame = pGame;
	m_pEntityKeeper = new EntityKeeper(this);

	InitializeScene();
	assert(m_pCamera != nullptr && "Scene has no assigned camera");
}

void Scene::Update(float deltaTime)
{
	m_pEntityKeeper->UpdateEntities(deltaTime);

	UpdateScene(deltaTime);
}

void Scene::Draw() const
{
	// Draw UI above here
	glPushMatrix();
	m_pCamera->Draw();
	m_pEntityKeeper->DrawEntities();

	DrawScene();
	glPopMatrix();
}
