#pragma once
#include <string>

class GameObject;

/// <summary>
/// 게임 오브젝트를 찾는 인터페이스 함수
/// </summary>
class IGameObjectQuery
{
public:
	/// <summary>
	/// 게임 오브젝트를 이름으로 찾는 함수
	/// </summary>
	/// <param name="name">게임 오브젝트 이름</param>
	/// <returns>찾으면 게임 오브젝트 포인터 아니면 nullptr</returns>
	virtual GameObject* FindByName(const std::string& name) const = 0;
	virtual ~IGameObjectQuery() = default;
};