#include "GameLogicTestScene.h"
#include "LiveObject/LiveObject.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "../CsvData/CsvDataManager.h"
#include "Utils/Singleton.h"
void GameLogicTestScene::OnEnterImpl()
{
	//menuObj = new GameObject(); // GameObject 객체 생성
	//menuObj->AddComponent<MenuTextObject>(); // MonoBehaivor 등록
	//AddGameObject(menuObj);	// Scene에 GameObject 추가
	
	CsvDataManager::GetInstance().SetCSV<AllNodePattenClass>("../../Resource/DataTable/노드 전체 패턴 테이블.csv", 5); // 데이터 파일 읽어오기
	CsvDataManager::GetInstance().PrintMap();
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