#include "GameLogicTestScene.h"
#include "../CsvData/CsvDataManager.h"
#include "../LogicTestManager/BettleManager.h"
#include "../LogicTestManager/AttackPatternManager.h"
#include "LiveObject/Player.h"
#include "LiveObject/Enemy.h"
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
	attackPattenManager = new GameObject();                    // GameObject 객체 생성
	attackPattenManager->AddComponent<AttackPatternManager>(); // MonoBehaivor 등록
	AddGameObject(attackPattenManager);	                       // Scene에 GameObject 추가
	
	bettleManager = new GameObject();             // GameObject 객체 생성
	bettleManager->AddComponent<BettleManager>(); // MonoBehaivor 등록
	AddGameObject(bettleManager);	              // Scene에 GameObject 추가

	player = new GameObject();      // GameObject 객체 생성
	player->AddComponent<StateController<Enemy>>();
	player->AddComponent<Player>(); // MonoBehaivor 등록
	AddGameObject(player);	        // Scene에 GameObject 추가

	enemy = new GameObject();	  // GameObject 객체 생성
	enemy->AddComponent<StateController<Enemy>>();
	enemy->AddComponent<Enemy>(); // MonoBehaivor 등록
	AddGameObject(enemy);		  // Scene에 GameObject 추가


	EnemyData* tmp = nullptr;
	//CsvDataManager::GetInstance().SetCSV<EnemyData>("../../Resource/DataTable/적 데이터 테이블.csv"); // 데이터 파일 읽어오기

	//tmp = CsvDataManager::GetInstance().getDataImpl<EnemyData>(tmp, "EI_006");
	//tmp->PrintMap();
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