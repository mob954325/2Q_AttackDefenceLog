#pragma once
#include "framework.h"

/// 2025.07.29 | 작성자 : 이성호
/// 오버로딩된 오퍼레이터 사용하려면 상속받는 객체의 역참조를 비교해야함  

/// <summary>
/// 모든 객체가 상속받는 클래스 ( 유니티에서의 Object를 담당 )
/// </summary>
class BaseObject
{
private:
	static constexpr uint64_t INVALID_ID = 0xFFFFFFFFFFFFFFFF;
	static uint64_t nextInstanceID;
	uint64_t instanceID = 0;

protected:
	std::string name = "";

public:
	BaseObject() : instanceID(INVALID_ID) {}
	virtual ~BaseObject() {}

	void SetInstanceID();
	uint64_t GetInstanceID() const;
	std::string GetName();
	void SetName(std::string str);

	static void Destroy(BaseObject obj, float t = 0.0f);
	static void Instantiate(BaseObject original);

	operator bool() const
	{
		return instanceID == INVALID_ID ? false : true;
	}

	bool operator !=(const BaseObject& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator ==(const BaseObject& rhs) const
	{
		return instanceID == rhs.GetInstanceID();
	}
};