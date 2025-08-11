#pragma once
#include "Utils/Singleton.h"
#include <queue>
#include <functional>

/* 25.08.11 | 작성자 : 이성호
* 기능 - Task의 fucntor를 점진적으로 실행해주는 시스템 매니저

	해당 시스템 클래스는 갑작스러운 오브젝트 생성이 주는 끊김을 줄이기 위해 만듦
	AddTask를 통해 실행할 함수를 Task의 형태로 등록하고 ProcessTaskQueeu
*/

struct Task
{
	std::function<void()> func; // 수행 할 내용의 void()형 함수
};

class TaskSystem : public Singleton<TaskSystem>
{
public:

	/// <summary>
	/// Task를 생성하여 taskQueue에 등록하는 함수 ( void() 형 functor 받음 )
	/// </summary>
	void AddTask(const std::function<void()>& func, bool isImmediate);

	/// <summary>	
	/// taskAmount만큼 taskQueue에 있는 task를 실행하는 함수
	/// </summary>
	/// <param name="taskAmount">실행할 task량</param>
	void ProcessTaskQueue(int taskAmount);

	/// <summary>
	/// taskQueue.size() 반환 함수
	/// </summary>
	/// <returns>taskQueue 크기</returns>
	int GetRemainTaskAmount();

	void Clear();

private:
	std::queue<Task> taskQueue{};
};

