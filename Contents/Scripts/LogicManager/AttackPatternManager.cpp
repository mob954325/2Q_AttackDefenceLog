#include "AttackPatternManager.h"
#include "Utils/GameTime.h"

struct pattern;

void AttackPatternManager::OnStart() {
	if (NowPatternStorage.size() != 0) {
		for (const auto& pair : NowPatternStorage) {
			delete pair.second;
		}
	}
	NowPatternStorage.clear();
}


void AttackPatternManager::AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID) {
	pattern* tmpPattern = new pattern();
	tmpPattern->PattenID = ID;
	tmpPattern->PlayingAttackTime = PlayingAttackTime;
	tmpPattern->TotalPlayingAttackTime = PlayingAttackTime;
	tmpPattern->NodePatten = PatternID;

	NowPatternStorage[ID] = tmpPattern;
}

void AttackPatternManager::OnUpdate() {
	bool isFirst = true;
	bool isSecond = false;
	int countNum = 0;	// 숫자 2개 일치하는지 검사하는 수
	for (const auto& pair : NowPatternStorage) {
		if (pair.first.substr(0, 2) == "PI") {
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
		else {  // 적 패턴만 시간계산
			if (pair.second->PlayingAttackTime == pair.second->TotalPlayingAttackTime) { // 처음 지점(일꺼임)
				isNewPattern = true;
				newPattern.pattern = pair.second->NodePatten;
				newPattern.totalTime = pair.second->TotalPlayingAttackTime;
				newPattern.PattenID = pair.second->PattenID;
			}

			pair.second->PlayingAttackTime -= GameTime::GetInstance().GetDeltaTime();

			if (pair.second->PlayingAttackTime <= 0.0f) { // 시간검사
				tmpTimeOutPattern[pair.first] = pair.second; // 시간 다 된패턴들 임시 저장소에 저장
				continue;
			}
		}

	}


	// 임시 저장된 패턴이 있다면 순회하면서 복사, 삭제하기!
	if (tmpTimeOutPattern.size() != 0) {
		for (const auto& pair : tmpTimeOutPattern) {
			NowPatternStorage.erase(pair.first);
			timeOutPattern[pair.first] = pair.second;
		}
		tmpTimeOutPattern.clear();
	}
}

//
void AttackPatternManager::SubPattern(std::string ID, bool isTime) {
	if (isTime) {
		auto it = timeOutPattern.find(ID);
		if (it != timeOutPattern.end()) {
			delete it->second;
			timeOutPattern.erase(it);
		}
	}
	else {
		auto it = NowPatternStorage.find(ID);
		if (it != NowPatternStorage.end()) {
			delete it->second;
			NowPatternStorage.erase(it);
		}
	}
}


pattern* AttackPatternManager::CorrectPattern(std::vector<int> PatternID) {  //해당 패턴의 성공여부

	// for (int i = 0; i < PatternID.size(); i++)
	// {
	// 	std::string str = std::to_string(PatternID[i]);
	// 	OutputDebugStringA(str.c_str());
	// 	OutputDebugStringA("\n");
	// }

	//순서 검사
	bool isVaild = true;
	for (const auto& pair : NowPatternStorage)
	{
		std::cout << pair.second->PattenID << std::endl;
		OutputDebugStringA(pair.second->PattenID.c_str());
		OutputDebugStringA("\n");
	}

	for (const auto& pair : NowPatternStorage) { // 적 패턴 
		int countNum = 0; // 맞은 개수 검
		if (pair.first.substr(0, 2) == "EP") {
			// 패턴 이중 for문 검사
			for (int i = 0; i < PatternID.size(); i++) {
				for (int j = 0; j < pair.second->NodePatten.size(); j++) {
					if (PatternID[i] == pair.second->NodePatten[j]) {
						countNum++; // 체크 // 적 패턴과 인풋이 겹친 갯수
					}
				}
			}

			// pair가 적 패턴 일 때
			if (countNum >= 2) // 적 방어를 시도했다 - 공격 무시
			{
				isVaild = false;
				OnPatternCancel.Invoke(pair.second->PattenID); // 패턴 캔슬된거 알림 -> 방어 성공
				// 방어 시도 countNun 2 ~ 4개, 패턴이 적일 때				
				
				//============================================================================(성공 실패)
				for (int i = 0; i < PatternID.size(); i++) {	// 현재 그은 패턴 검사
					if (PatternID[i] != pair.second->NodePatten[i]) { // 그은 패턴과 적 패턴이 맞지 않음

						pair.second->isFail = true; // 방어 실패
						break;
					}

					return pair.second; // 성공
				}
				//============================================================================(
			}
			// pair가 플레이어 가이드 패턴 일 때
		}
	}

	if (isVaild) {
		for (const auto& pair : NowPatternStorage) { // 적 패턴 / 가이드 패턴
			if (pair.first.substr(0, 2) == "PI") {      // 패턴이 플레이어의 패턴이면 정방향 검사
				for (int i = 0; i < PatternID.size(); i++) {
					if (PatternID[i] != pair.second->NodePatten[PatternID.size() - 1 - i]) { // 역순으로 검사
						pair.second->isFail = true;
						break;
					}

					return pair.second; // 성공
				}

			}
		}
	}

	return nullptr;     // 공격 실패, 방어 실패 시 nullptr 반환
}


pattern* AttackPatternManager::failPattern(std::vector<int> PatternID) { // 공격 , 방어 실패여부!
	for (const auto& pair : NowPatternStorage) {
		if (pair.second->isFail == true) {
			if (pair.second->PattenID.substr(0, 2) == "PI") {
				playerPatternA = playerPatternB = { 0 }; // 벡터 잠시 비워두기					
			}
			return pair.second;
		}
	}
	return nullptr;
}

//타임아웃 패턴 호출하고 삭제해주기!!!
pattern* AttackPatternManager::TimeOutPatten() {
	if (timeOutPattern.size() != 0) {
		auto it = timeOutPattern.begin();
		return it->second;
	}
	return nullptr;
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
	SubPattern(tmp, false);
}



