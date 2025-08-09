#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/PatternDrawerComponent.h"
#include "Objects/Scenes/Stage/NodeObject.h"

/*  25.08.08 | 작성자 : 이성호
*   기능 : titleScene의 노드관리를 하는 MonoBehavior로 
			노드 두 개 연결 되었는지 확인하는 함수
*/

class TitleNodeManager : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void HandleSliceNode();
	void HandleSceneChangeTimer();

private:
	PatternDrawerComponent* patternDrawer;
	std::vector<NodeObject*> nodes; // 입력용 노드
	std::vector<bool> nodeOverlap;	// 각 인덱스 노드가 겹쳤는지 확인하는 컨테이너

	float gap = 300;	// 두 노드 사이의 간격

	bool isSlice = false; // 두 노드를 그었는지 확인하는 변수
	bool isSceneChange = false; // 씬 교체하는 지 확인하는 함수 - 중복 호출 방지용

	float timer = 0.0f;
	float maxTimer = 3.0f;
};