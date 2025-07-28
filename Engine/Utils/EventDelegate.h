#pragma once
// <example>
// 등록 방식
// 1. Add() 사용
// ListenerID id1 = player->OnHpChange.Add(std::bind(&HpComponent::ChangeValue, this, std::placeholders::_1));
// 
// 2. += 오퍼레이터 사용
// id2 = player->OnHpChange += std::bind(&HpComponent::ChangeValue2, this, std::placeholders::_1);
// 
// 3. 람다 함수 사용
// id2 = player->OnHpChange += [](int _) { std::cout << "Call lambda expresstion functoin by action class \n"; };
// 
// 4. = 오퍼레이터 사용
// player->OnHpChange = std::bind(&HpComponent::EqualOperatorEvent, this);
// 
// 제거
// 1. RemoveByID 함수 사용
// player->OnHpChange.RemoveByID(id2);
// </example>

// NOTE: operator-= is intentionally not supported due to std::function comparison limitations.
//		 operator-=는 std::function의 비교제한으로 인해 지원하지 않습니다.
//		 연산자 오버로딩은 +=, = 만 지원합니다.

// NOTE2: 현재 코드는 ListnerID의 고유 값을 저장안하면 제거할 수 없습니다. 반드시 해당 값을 저장하고 사용하세요
//		  ListenerID는 고유 값이기 때문에 중복 저장을하면 덮어씌워진 값은 찾을 수 없습니다.


using ListenerID = size_t;

template <typename ...Args>
class EventDelegate
{
	struct Event
	{
		ListenerID id;	// Event의 유일한 아이디 값
		std::function<void(Args...)> func;	// 등록된 함수
	};

public:
	ListenerID Add(const std::function<void(Args...)>& refFunc)
	{
		ListenerID id = nextId++;
		listeners.push_back({ id, refFunc });
		return id;
	}

	void RemoveByID(ListenerID targetId)
	{
		auto it = listeners.begin();
		for (; it != listeners.end();)
		{
			if (it->id == targetId)
			{
				it = listeners.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void Clear()
	{
		listeners.clear();
	}

	void Invoke(Args... args) const
	{
		for (const Event& e : listeners)
		{
			e.func(args...);
		}
	}

	ListenerID operator+=(const std::function<void(Args...)>& func)
	{
		return Add(func);
	}

	void operator=(const std::function<void(Args...)>& func)
	{
		listeners.clear();
		Add(func);
	}

public:
	EventDelegate() = default;
	~EventDelegate() = default;

private:
	std::vector<Event> listeners;
	ListenerID nextId = 0;
};
