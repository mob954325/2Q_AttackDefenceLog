#pragma once
#include "pch.h"
#include "Utils/Singleton.h"
#include "Component.h"
#include "Transform.h"
#include "Datas/EngineData.h"
#include "Scene/GameObjectQuery.h"
#include "BaseObject.h"
#include "MonoBehavior.h"
#include <queue>

/// <summary>
/// 모든 게임 오브젝트가 상속받는 클래스로 Component만 담고 Component관련 함수만 포함되어있음
/// </summary>
class GameObject : public BaseObject
{
public:
	GameObject();
	virtual ~GameObject();

	template <typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		T* comp = new T;
		comp->owner = this;

		comp->SetInstanceID();
		CheckComponent(comp);
		return comp;
	}

	template <typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (Component* mono : monoBehaviors)
		{
			if (typeid(*mono) == typeid(T))
			{
				return static_cast<T*>(static_cast<Component*>(mono));
			}
		}

		for (Component* comp : components)
		{
			if (typeid(*comp) == typeid(T))
			{
				return static_cast<T*>(static_cast<Component*>(comp));
			}
		}

		return nullptr;
	}

	void ProcessStartQeue();
	void Destroy();

	void RemoveComponent(Component* targetComp);

	// 오브젝트 제거 관련
	void MarkForRemoval() { shouldRemove = true; };				// 제거할 오브젝트라고 마킹
	bool IsMarkedForRemoval() const { return shouldRemove; }

	// 오브젝트 추가 관련
	void MarkSetupComplete() { isActiveInScene = false; };			// 추가된 오브젝트라고 마킹
	bool IsActiveInScene() const { return isActiveInScene; }
	
	// get/set
	EngineData::RenderLayer GetRenderLayer() const;

	void SetRenderLayer(int value);
	void SetRenderLayer(EngineData::RenderLayer layerType);
	int GetRenderLayerIndex() const;

	void SetQueryInterface(IGameObjectQuery* q);

	Transform& GetTransform();

protected:
	EngineData::RenderLayer renderLayer = EngineData::RenderLayer::None;
	IGameObjectQuery* query = nullptr;

private:
	void CheckComponent(Component* comp);
	void DispatchComponentToSystem(Component* comp);
	void RemoveComponentToSystem(Component* comp);

	Transform* transform = {};
	std::vector<MonoBehavior*> monoBehaviors;	// MonoBehaivor 컴포넌트만 담는 컨테이너
	std::vector<Component*> components;			// 컴포넌트를 담는 컨테이너
	std::queue<Component*> startQueue;			// start를 실행하지 않은 컴포넌트 모음
	bool shouldRemove = false;					// 해당 오브젝트가 다음 프레임에 제거될 대상인지 확인하는 변수 ( 제거예정이면 true )
	bool isActiveInScene = true;					// 해당 오브젝트가 이번 프레임에 생성되었는지 확인하는 변수 ( 생성된 후 다음 프레임에 false로 전환 )
};