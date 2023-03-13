// ReSharper disable once CppUnusedIncludeDirective, This is pch
#include "base.h"

#include "Component.h"

Component::Component(Entity* parent)
	: m_pParent{ parent }
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}
