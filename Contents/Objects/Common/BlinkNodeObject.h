#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Rendering/BitmapRenderer.h"

#include <array>

class BlinkNodeObject : public MonoBehavior
{
public:	
	void OnStart() override;
	void OnCreate() override;
	void OnUpdate() override;	

	void Start(std::vector<int> pattern, bool isE = false);

	void Stop(); 
	void SetupNodes(Vector2 node, float interval); // 중앙의 노드 좌표와 간격을 넣어주세오
	
private:
	bool isPlay = false;
	bool isEnemy = false;
	bool isReverse = false;
	float progress = 0.0f; // 0 ~1 정규화된 값이 들어가야함

	std::array<Vector2, 9> positions; // 좌표값들

	std::vector<BitmapRenderer*> playerBlinkBitmaps;	
	std::vector<BitmapRenderer*> enemyBlinkBitmaps;
	std::vector<int> path;

};