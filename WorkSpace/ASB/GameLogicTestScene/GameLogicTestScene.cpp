#include "GameLogicTestScene.h"
#include "LiveObject/LiveObject.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "../CsvData/DataClass/PlayerData.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/CsvDataManager.h"
#include "Utils/GameTime.h"
#include "Utils/Singleton.h"

/*
	업데이트 순서
    플레이어  업데이트 : 대부분 시간에 따라 변화하는 것들 처리
    적 업데이트
    배들 매니저 업데이트
    state 매니저 업데이트

	!!! 주의 !!!
	씬 단위로 시간을 통일시키기!!
 */

void GameLogicTestScene::OnEnterImpl()
{

	//menuObj = new GameObject(); // GameObject 객체 생성
	//menuObj->AddComponent<MenuTextObject>(); // MonoBehaivor 등록
	//AddGameObject(menuObj);	// Scene에 GameObject 추가
	
	EnemyData* tmp = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyData>("../../Resource/DataTable/적 데이터 테이블.csv"); // 데이터 파일 읽어오기
	tmp = CsvDataManager::GetInstance().getDataImpl<EnemyData>(tmp, "EI_006");
	tmp->PrintMap();
}

void GameLogicTestScene::OnExitImpl()
{

}

void GameLogicTestScene::UpdateImpl()
{
	while (1) {
		int a = 1;
		a + 1;
	}
}