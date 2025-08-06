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

void AttackPatternManager::AddPattern(std::string ID, float PlayingAttackTime, std::vector<int> PatternID){
	pattern* tmpPattern = new pattern();
	tmpPattern->PattenID = ID;
	tmpPattern->PlayingAttackTime = PlayingAttackTime;
	tmpPattern->TotalPlayingAttackTime = PlayingAttackTime;
	tmpPattern->NodePatten = PatternID;

	NowPatternStorage[ID] = tmpPattern;
}

void AttackPatternManager::OnUpdate() {
	for (const auto& pair : NowPatternStorage) {
		pair.second->PlayingAttackTime -= GameTime::GetInstance().GetDeltaTime();
	}
}

void AttackPatternManager::SubPattern(std::string ID) {
	auto it = NowPatternStorage.find(ID);
	if (it != NowPatternStorage.end()) {
		delete it->second;
		NowPatternStorage.erase(it);
	}
}


pattern* AttackPatternManager::CorrectPattern(std::vector<int> PatternID){
	bool isCorrect = false;
	for (const auto& pair : NowPatternStorage) { 
		if (pair.first.substr(0, 2) == "EP") {   // 패턴이 적이면 
			for (int i = 0; i < PatternID.size(); i++) {
				if (PatternID[i] != pair.second->NodePatten[PatternID.size() - 1 - i]) { // 역순으로 검사
					isCorrect = false;   //하나라도 맞지 않으면 for문 탈출
					break;
				}
				isCorrect = true;        // 끝까지 루프를 돌면 성공
			}
			
		}    
		else {      // 패턴이 플레이어의 패턴이면 정방향 검사
			for (int i = 0; i < PatternID.size(); i++) {  
				if (PatternID[i] != pair.second->NodePatten[i]) {  
					isCorrect = false;  // 하나라도 맞지 않으면 for문 탈출
					break;
				}
				isCorrect = true;       // 끝까지 루프를 돌면 성공
			}
			
		}
		if (isCorrect)  // 성공이면 patten* return
			return pair.second;
	}
	return nullptr;     // 실패면, null return
}

pattern* AttackPatternManager::TimeOutPatten() {
	for (const auto& pair : NowPatternStorage) {
		if (pair.second->PlayingAttackTime <= 0.0f) {
			return  pair.second;
		}
		else
			return nullptr;
	}
}

//void AttackPatternManager
