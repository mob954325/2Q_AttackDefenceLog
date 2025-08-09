#include "AttackPatternManager.h"
#include "Utils/GameTime.h"

struct pattern;

void AttackPatternManager::OnStart() {
	if (NowPlayerStorage.size() != 0) {
		for (const auto& pair : NowPlayerStorage) {
			delete pair.second;
		}
	}
	NowPlayerStorage.clear();

	if (NowEnemyStorage.size() != 0) {
		for (const auto& pair : NowEnemyStorage) {
			delete pair.second;
		}
	}
	NowEnemyStorage.clear();
}

//패턴을 추가하는 함수 적과 플레이어의 패턴의 저장소가 다름
void AttackPatternManager::AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID) {
	pattern* tmpPattern = new pattern();
	tmpPattern->PattenID = ID;
	tmpPattern->PlayingAttackTime = PlayingAttackTime;
	tmpPattern->TotalPlayingAttackTime = PlayingAttackTime;
	tmpPattern->NodePatten = PatternID;
	for (int i = 0; i < PatternID.size(); ++i) {
		if (PatternID[i] == 0 && i > 0) {
			tmpPattern->lastPosition = ConvertEndNodeToPosition(PatternID[i-1]);
			break;
		}
	}

	if (tmpPattern->PattenID.substr(0, 2) == "PI") {
		NowPlayerStorage[ID] = tmpPattern;
	}
	else if (tmpPattern->PattenID.substr(0, 2) == "EP") {
		NowEnemyStorage[ID] = tmpPattern;
	}
}


//
void AttackPatternManager::OnUpdate() {
	bool isFirst = true;
	bool isSecond = false;
	int countNum = 0;	// 숫자 2개 일치하는지 검사하는 수
	for (const auto& pair : NowPlayerStorage) {
		if (isFirst) { // 시간이 남고, 플레이어의 첫번쩨 패턴 이면 저장
				playerPatternA = pair.second->NodePatten;
				isSecond = true;
				isFirst = false;
		}
		else if (isSecond) // 시간이 남고, 플레이어의 두번쩨 패턴이면 저장
		{
				playerPatternB = pair.second->NodePatten;
				isSecond = false;
		}
	}

	// 현재 새로 생성되어 있는 적 패턴의 정보를  따로 저장 -> 패턴 UI에 사용할것!
	for(const auto& pair : NowEnemyStorage){
		if (pair.second->PlayingAttackTime == pair.second->TotalPlayingAttackTime) { //
			isNewPattern = true;
			newPattern.pattern = pair.second->NodePatten;
			newPattern.totalTime = pair.second->TotalPlayingAttackTime;
			newPattern.PattenID = pair.second->PattenID;
		}

		pair.second->PlayingAttackTime -= GameTime::GetInstance().GetDeltaTime(); // 패턴의 시간 감소

		if (pair.second->PlayingAttackTime <= 0.0f) { // 시간검사
			tmpTimeOutPattern[pair.first] = pair.second; // 시간 다 된패턴들 임시 저장소에 저장				
			continue;
		}
	}

	// 임시 저장된 패턴이 있다면 순회하면서 복사, 삭제하기!
	if (tmpTimeOutPattern.size() != 0) {
		for (const auto& pair : tmpTimeOutPattern) {
			NowEnemyStorage.erase(pair.first);
			timeOutPattern[pair.first] = pair.second;
		}
		tmpTimeOutPattern.clear();
	}
}

//각 string에 따라 다른 저장소에서 해당 패턴의 ID를 찾아 제거!
void AttackPatternManager::SubPattern(std::string ID, std::string StorageType) {
	if (StorageType == "Time") {
		auto it = timeOutPattern.find(ID);
		if (it != timeOutPattern.end()) {
			delete it->second;
			timeOutPattern.erase(it);
		}
	}
	else if (StorageType == "Player") {
		auto it = NowPlayerStorage.find(ID);
		if (it != NowPlayerStorage.end()) {
			delete it->second;
			NowPlayerStorage.erase(it);
		}
	}
	else if (StorageType == "Enemy") {
		auto it = NowEnemyStorage.find(ID);
		if (it != NowEnemyStorage.end()) {
			delete it->second;
			NowEnemyStorage.erase(it);
		}
	}
}; 


pattern* AttackPatternManager::CorrectPattern(std::vector<int> PatternID) {  //해당 패턴의 성공여부
	//순서 검사
	bool isVaild = true;
	bool isPlayerSearch = true;
	int EnemyZero = 0;   
	int PlayerZero1 = 0;
	int PlayerZero2 = 0;
	//적 검사

	//적 패턴 검사
	for (const auto& pair : NowEnemyStorage) { // 적 패턴 
		
		for (int j = 0; j < pair.second->NodePatten.size(); j++) { // 0 개수 검사
			if (pair.second->NodePatten[j] == 0)
			{
				EnemyZero++;
			}
		}


		int countNum = 0; // 맞은 개수 검사
		for (int i = 0; i < PatternID.size(); i++) {
			for (int j = 0; j < pair.second->NodePatten.size() - EnemyZero; j++) {
				if (PatternID[i] == pair.second->NodePatten[j]) {
					countNum++; // 체크 // 적 패턴과 인풋이 겹친 갯수
				}
			}
		}

		// 적 패턴이 2 이상이면 방어 패턴으로 처리
		if (countNum >= 2) {
			isPlayerSearch = false; // 공격 처리 안함!!
			//isAttack = false;
			// 방어 시도 countNun 2 ~ 4개, 패턴이 적일 때				
			
			if (PatternID.size() != pair.second->NodePatten.size() - EnemyZero) 
			{ //입력 노드와 0을 제외한 적 공격 노드의 개수가 같지 않다면
				isPlayerSearch = false; // 플레이어 가이드라인 판정함
				pair.second->isFail = true; // 방어 실패
				break;  // 적 방어 판정 끝
			}


			for (int i = 0; i < PatternID.size(); i++) {	// 현재 그은 패턴 검사
				if (PatternID[i] != pair.second->NodePatten[PatternID.size() -1 - i ]) { // 그은 패턴과 적 패턴이 맞지 않음

					pair.second->isFail = true; // 방어 실패
					return nullptr;
				}
				if (i == PatternID.size() - 1) {
					OnPatternCancel.Invoke(pair.second->PattenID); // 패턴 캔슬된거 알림 -> 방어 성공
					return pair.second; // 성공
				}
			}
		}
		else {
			// 공격 시도
			isPlayerSearch = true;
		}
	}
	//플레이어의 공격 시도로  처리
	if (isPlayerSearch) {
		for (const auto& pair : NowPlayerStorage) {
			int playerCountZero = 0;
			for (int j = 0; j < pair.second->NodePatten.size(); j++) { // 0 개수 검사
				if (pair.second->NodePatten[j] == 0)
				{
					playerCountZero++;
				}
			}
			if (PatternID.size() != pair.second->NodePatten.size() - playerCountZero) { //입력 노드와 0을 제외한 적 공격 노드의 개수가 같지 않다면
				pair.second->isFail = true; // 공격 실패판정
				//isAttack = false;
				break;
			}
			for (int i = 0; i < PatternID.size(); i++) {	// 현재 그은 패턴 검사
				if (PatternID[i] != pair.second->NodePatten[i]) { // 그은 패턴과 적 패턴이 맞지 않음
					pair.second->isFail = true; // 공격 실패
					//isAttack = false;
					break;
				}
				//
				if( i == PatternID.size() -1){
					playerPatternA = playerPatternB = { 0 }; // 벡터 잠시 비워두기
					isAttack = true; // 공격임(성공임)
					isAttackVec = PatternID;
					return pair.second; // 성공
				}
					
			}
		}
		return nullptr;
	}
	return nullptr;     // 공격 실패, 방어 실패 시 nullptr 반환
}


pattern* AttackPatternManager::failPattern(std::vector<int> PatternID) { // 공격 , 방어 실패여부!
	for (const auto& pair : NowEnemyStorage) {
		if (pair.second->isFail == true) {
			return pair.second;
		}
	}

	for (const auto& pair : NowPlayerStorage) {
		if (pair.second->isFail == true) {
			playerPatternA = playerPatternB = { 0 }; // 벡터 잠시 비워두기
			return pair.second;
		}
	}
	return nullptr;
}


//타임아웃 패턴 호출하고 삭제해주기!!!
std::unordered_map<std::string, pattern*>  AttackPatternManager::TimeOutPatten() {
	return timeOutPattern;
}


// 타임 아웃 패턴 다 사용했으면 타임 클리어
void AttackPatternManager::DoneTimeOutPatten(){
	timeOutPattern.clear();
}



void AttackPatternManager::GetPlayerPatten(std::vector<int>& P1, std::vector<int>& P2) // 갱신 1초
{
	P1 = playerPatternA;
	P2 = playerPatternB;
}


void AttackPatternManager::GetEnemyPattern(std::vector<int>& pattern, float& time, std::string& ID)
{
	isNewPattern = false;
	pattern = newPattern.pattern;
	time = newPattern.totalTime;
	ID = newPattern.PattenID;
}


//커플 모두 도륙
void AttackPatternManager::SearchAndDestroyCouple(std::string ID) {
	char a = ID.back();
	std::string tmp;
	if (a == 'A') {
		tmp = ID.substr(0, ID.length() - 1);
		tmp.push_back('B');
	}
	else if (a == 'B') {
		tmp = ID.substr(0, ID.length() - 1);
		tmp.push_back('A');
	}
	SubPattern(tmp, "Player");
}



//마지막 노드를 입력하면 상, 중, 하 enum 상태로 바꿈 
AttackPosition AttackPatternManager::ConvertEndNodeToPosition(int endNode) {
	switch (endNode)
	{
	case 1:  return UpNode;
	case 2:  return UpNode;
	case 3:  return UpNode;
	case 4:  return MiddleNode;
	case 5:  return MiddleNode;
	case 6:  return MiddleNode;
	case 7:  return LowNode;
	case 8:  return LowNode;
	case 9:  return LowNode;
	default: return NonePos;
	}
}
