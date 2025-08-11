#include "TaskSystem.h"
#include <iostream>
#include "Utils/DebugUtility.h"

void TaskSystem::AddTask(const std::function<void()>& func, bool isImmediate)
{
	if (isImmediate)
	{
		func();
	}
	else
	{
		Task newTask = { func };
		taskQueue.push(newTask);

	}
}

void TaskSystem::ProcessTaskQueue(int taskAmount)
{
	int remainTask = taskAmount;

	while ((!taskQueue.empty() && remainTask > 0))
	{
		Task currTask = taskQueue.front();
		taskQueue.pop();

		currTask.func(); // 등록된 함수 실행
		
		remainTask--;

		DebugUtility::Print("task 처리 완료");
	}
}

int TaskSystem::GetRemainTaskAmount()
{
	return taskQueue.size();
}

void TaskSystem::Clear()
{
	while (!taskQueue.empty())
	{
		taskQueue.pop();
	}
}