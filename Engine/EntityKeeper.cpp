#include "base.h"
#include "EntityKeeper.h"

#include "Entity.h"

EntityKeeper::EntityKeeper(Scene* scene)
    : m_pScene{ scene }
{
}

EntityKeeper::~EntityKeeper()
{
    for (const Entity* entity : m_Entities)
    {
        delete entity;
    }
}

Entity* EntityKeeper::CreateEntity()
{
    return CreateEntity(0, "");
}

Entity* EntityKeeper::CreateEntity(int updatePriority)
{
    return CreateEntity(updatePriority, "");
}

Entity* EntityKeeper::CreateEntity(int updatePriority, const std::string& tag)
{
	Entity* newEnt = new Entity(m_pScene, updatePriority);
    newEnt->SetTag(tag);

    // insert object correctly based on update priority
	std::list<Entity*>::iterator iter = m_Entities.begin();
    while (iter != m_Entities.end() && (*iter)->GetUpdatePriority() < updatePriority)
    {
        ++iter;
    }

    m_Entities.insert(iter, newEnt);

    return newEnt;
}

void EntityKeeper::DeleteEntity(Entity* entity)
{
    if (entity == nullptr) return;

    m_Entities.remove(entity);
    delete entity;
}

void EntityKeeper::UpdateEntities(float deltaTime) const
{
    for (const Entity* entity : m_Entities)
    {
        for (Component* comp : entity->GetComponents())
        {
            comp->Update(deltaTime);
        }
    }
}

void EntityKeeper::DrawEntities() const
{
    for (const Entity* entity : m_Entities)
    {
        for (const Component* comp : entity->GetComponents())
        {
			glPushMatrix();
            comp->Draw();
			glPopMatrix();
        }
    }
}

Entity* EntityKeeper::GetEntityWithTag(const std::string& tag) const
{
    for (Entity* e : m_Entities)
    {
        if (e->GetTag() == tag) return e;
    }
    return nullptr;
}
