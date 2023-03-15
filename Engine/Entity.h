#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Component.h"

class EntityKeeper;
class Scene;

class Entity final
{
public:
	Entity& operator=(const Entity& rhs) = delete;
	Entity& operator=(Entity&& rhs) = delete;
	Entity(const Entity& rhs) = delete;
	Entity(Entity&& rhs) = delete;

	template<typename TComponent>
	TComponent* GetComponent() const;
	void AddComponent(Component* comp);
	std::vector<Component*> GetComponents() const;

	void Initialize() const;

	// Non-Unique Identifiers that can be used to filter Entities
	const std::string& GetTag() const;
	void SetTag(const std::string& newTag);

	// Inactive Entities are neither updated nor drawn
	void SetActive(bool newState);
	bool IsActive() const;

	Scene* GetScene() const;

	// Entities and all components within them are updated
	// from highest update priority to lowest, so this value
	// determines things like render order (!)
	int GetUpdatePriority() const;

private:
	Scene* m_pScene;

	const int m_UpdatePriority;

	bool m_IsActive = true;
	std::vector<Component*> m_Components;
	std::string m_Tag;

	// Allow only EntityKeeper to manage lifecycle of Entities
	explicit Entity(Scene* scene, int updatePriority);
	~Entity();
	friend class EntityKeeper;
};

// Definition in header because templates are... interesting
// Fetches Component of type TComponent if this Entity has it
template<typename TComponent>
TComponent* Entity::GetComponent() const
{
	static_assert(std::is_base_of_v<Component, TComponent>, "Provided template argument is not a component");

	for (Component* comp : m_Components)
	{
		auto* castComponent = dynamic_cast<TComponent*>(comp);
		if (castComponent) return castComponent;
	}

	return nullptr;
}