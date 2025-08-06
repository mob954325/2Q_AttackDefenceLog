#include "GameLogicTestScene.h"
#include "../CsvData/CsvDataManager.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "../CsvData/DataClass/EnemyAtkPattenData.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/DataClass/PlayerData.h"
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
	PlayerAtkPetternData* tmp1 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyData>("../../Resource/DataTable/적 데이터 테이블.csv"); // 데이터 파일 읽어오기


	EnemyAtkPattenData* tmp2 = nullptr;
	CsvDataManager::GetInstance().SetCSV<EnemyAtkPattenData>("../../Resource/DataTable/적 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	AllNodePattenClass* tmp3 = nullptr;
	CsvDataManager::GetInstance().SetCSV<AllNodePattenClass>("../../Resource/DataTable/노드 전체 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerAtkPetternData* tmp4 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerAtkPetternData>("../../Resource/DataTable/플레이어 공격 패턴 테이블.csv"); // 데이터 파일 읽어오기

	PlayerData* tmp5 = nullptr;
	CsvDataManager::GetInstance().SetCSV<PlayerData>("../../Resource/DataTable/플레이어 데이터 테이블.csv"); // 데이터 파일 읽어오기

	/*tmp1 = CsvDataManager::GetInstance().getDataImpl<PlayerAtkPetternData>(tmp1, "PI_006");
	tmp1->PrintMap();*/



	attackPattenManager = new GameObject();                    // GameObject 객체 생성
	attackPattenManager->AddComponent<AttackPatternManager>(); // MonoBehaivor 등록
	attackPattenManager->SetName("AttackPattenManager");
	AddGameObject(attackPattenManager);	                       // Scene에 GameObject 추가
	


	enemy = new GameObject();	  // GameObject 객체 생성
	auto enemytmp = enemy->AddComponent<Enemy>(); // MonoBehaivor 등록
	enemytmp->m_State = enemy->AddComponent<StateController>();
	enemy->SetName("Enemytmp");
	AddGameObject(enemy);		  // Scene에 GameObject 추가


	player = new GameObject();      // GameObject 객체 생성
	
	auto playertmp = player->AddComponent<Player>(); // MonoBehaivor 등록
	playertmp->m_State = player->AddComponent<StateController>();
	player->SetName("Playertmp");
	AddGameObject(player);	        // Scene에 GameObject 추가


	bettleManager = new GameObject();             // GameObject 객체 생성
	auto bettletmp = bettleManager->AddComponent<BettleManager>(); // MonoBehaivor 등록
	bettletmp->m_Enemy = enemytmp;
	bettletmp->m_Player = playertmp;
	bettleManager->SetName("BettleManager");
	AddGameObject(bettleManager);	              // Scene에 GameObject 추가


}

void GameLogicTestScene::OnExitImpl()
{

}

void GameLogicTestScene::UpdateImpl()
{
	
}