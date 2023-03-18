#include "base.h"

#include "Component.h"

#include "Entity.h"
#include "Scene.h"

Component::Component(Entity* parent)
	: m_pParent{ parent }
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}

EntityKeeper* Component::GetEntityKeeper() const
{
	return m_pParent->GetScene()->GetEntityKeeper();
}

PhysicsHandler* Component::GetPhysicsHandler() const
{
	return m_pParent->GetScene()->GetPhysicsHandler();
}
