#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"



/* 8.14. 한승규
* 플레이어의 공격/방어 판정에 따라
* 현재 상태를 표지판(글자)로 표시해주는 컴포넌트
* 이미지 5개(표지판)을 가지고 좌표는 동일하게 가지며
* 연출적으로 나왔다 들어갔다를 반복할듯
*
* 외부에서 호출되면, 1개만 호출되는게 보장됨(호출될때마다 다른 모든 사인이 ActiveFalse 시킴)
*/

class SignBoard : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	//공격 상 중 하
	void ShowHighSign();
	void ShowMiddleSign();
	void ShowLowSign();
	
	//이거 두개만 사용함, 사실 다른거도 쓰긴함
	void ShowOver();
	void ShowCorner();

	//패링 가드
	void ShowParrySign();
	void ShowGuardSign();

	// 현재 진행중인 모든 사인을 지움
	void ClearAllSigns();

protected:
	float progress = 0.0f;
	
	bool isPlay = false;

	std::vector<BitmapRenderer*> signBitmaps;	

	enum SignType { // Vector 인덱스랑 동일하게 사용함
		HighAttackSign = 0,
		MiddleAttackSign = 1,
		LowAttackSign = 2,
		GuardSign = 3,
		ParrySign = 4,
		Over = 5, //추가기능
		Corner =6

	};

	SignType type = GuardSign;
};


