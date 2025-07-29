#include "GameObject.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/MonoBehaviorSystem.h"

GameObject::GameObject()
{
	transform = AddComponent<Transform>(); // GameObject는 무조건 Transform를 하나 소유함
}

GameObject::~GameObject()
{
	// Destroy();
}

void GameObject::ProcessStartQeue()
{
	while (!startQueue.empty())
	{
		Component* comp = startQueue.front();
		startQueue.pop();

		comp->OnStart();
		comp->SetStarted();
	}
}

void GameObject::Destroy()
{
	for (Component* comp : components)
	{
		comp->OnDestroy();
		RemoveComponentToSystem(comp);
		delete comp;
	}
	components.clear();

	for (MonoBehavior* mb : monoBehaviors)
	{
		mb->OnDestroy();
		RemoveComponentToSystem(mb);
		delete mb;
	}
	monoBehaviors.clear();
}

void GameObject::RemoveComponent(Component* targetComp)
{
	for (auto it = components.begin(); it != components.end();)
	{
		if (*it == targetComp)
		{
			RemoveComponentToSystem(*it);
			delete* it;
			it = components.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameObject::CheckComponent(Component* comp)
{
	if (!*comp)
	{
		std::cerr << "[ " << comp->GetName() << " ] is INVALID" << std::endl;
		assert(false && "Invalid component");
	}

	if (MonoBehavior* mb = dynamic_cast<MonoBehavior*>(comp))
	{
		monoBehaviors.push_back(mb);
	}
	else
	{
		components.push_back(comp);
	}

	DispatchComponentToSystem(comp);
	comp->OnCreate(); // 즉시 OnCreate 호출
	comp->SetCreated();
	startQueue.push(comp);
}

void GameObject::DispatchComponentToSystem(Component* comp)
{
	if (ScriptComponent* sc = dynamic_cast<ScriptComponent*>(comp))
	{
		Singleton<ScriptSystem>::GetInstance().Register(sc);
	}
	else if (RenderComponent* rc = dynamic_cast<RenderComponent*>(comp))
	{
		Singleton<RenderSystem>::GetInstance().Register(rc);
	}
	else if (CollisionComponent* cc = dynamic_cast<CollisionComponent*>(comp))
	{
		Singleton<CollisionSystem>::GetInstance().Register(cc);
	}
	else if (PhysicComponent* pc = dynamic_cast<PhysicComponent*>(comp))
	{
		Singleton<PhysicSystem>::GetInstance().Register(pc);
	}
	else if (Transform* t = dynamic_cast<Transform*>(comp))
	{
		Singleton<TransformSystem>::GetInstance().Register(t);
	}
	else if (MonoBehavior* mb = dynamic_cast<MonoBehavior*>(comp))
	{
		Singleton<MonoBehaviorSystem>::GetInstance().Register(mb);
	}
}

void GameObject::RemoveComponentToSystem(Component* comp)
{
	if (ScriptComponent* sc = dynamic_cast<ScriptComponent*>(comp))
	{
		Singleton<ScriptSystem>::GetInstance().UnRegister(sc);
	}
	else if (RenderComponent* rc = dynamic_cast<RenderComponent*>(comp))
	{
		Singleton<RenderSystem>::GetInstance().UnRegister(rc);
	}
	else if (CollisionComponent* cc = dynamic_cast<CollisionComponent*>(comp))
	{
		Singleton<CollisionSystem>::GetInstance().UnRegister(cc);
	}
	else if (PhysicComponent* pc = dynamic_cast<PhysicComponent*>(comp))
	{
		Singleton<PhysicSystem>::GetInstance().UnRegister(pc);
	}
	else if (Transform* t = dynamic_cast<Transform*>(comp))
	{
		Singleton<TransformSystem>::GetInstance().UnRegister(t);
	}
	else if (MonoBehavior* mb = dynamic_cast<MonoBehavior*>(comp))
	{
		Singleton<MonoBehaviorSystem>::GetInstance().UnRegister(mb);
	}
}

EngineData::RenderLayer GameObject::GetRenderLayer() const
{
	return renderLayer;
}

void GameObject::SetRenderLayer(int value)
{
	renderLayer = (EngineData::RenderLayer)value;
}

void GameObject::SetRenderLayer(EngineData::RenderLayer layerType)
{
	renderLayer = layerType;
}

int GameObject::GetRenderLayerIndex() const
{ 
	return (int)renderLayer; 
}

void GameObject::SetQuery(IGameObjectQuery* q) 
{ 
	query = q; 
}

IGameObjectQuery* GameObject::GetQuery()
{
	return query;
}

Transform& GameObject::GetTransform()
{
	return *transform;
}