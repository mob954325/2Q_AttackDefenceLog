#include "GameLogicTestScene.h"
#include "LiveObject/LiveObject.h"
#include "../DataStorage/CsvDataStorage.h"
#include "../DataStorage/DataClass/AllNodePattenClass.h"
void GameLogicTestScene::OnEnterImpl()
{
	//menuObj = new GameObject(); // GameObject 객체 생성
	//menuObj->AddComponent<MenuTextObject>(); // MonoBehaivor 등록
	//AddGameObject(menuObj);	// Scene에 GameObject 추가
	CsvDataStorage<AllNodePattenClass> csvDataStorage; // CsvDataStorage 객체 생성
	csvDataStorage.SetCSV("../../Resource/DataTable/노드 전체 패턴 테이블.csv", 5); // 데이터 파일 읽어오기
	csvDataStorage.PrintMap();
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