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
		if (pair.first.substr(0, 2) == "EP") {
			for (int i = 0; i < PatternID.size(); i++) {
				if (PatternID[i] != pair.second->NodePatten[PatternID.size() - 1 - i]) {
					isCorrect = false;
					break;
				}
				isCorrect = true;
			}
			return pair.second;
		}
		else {
			for (int i = 0; i < PatternID.size(); i++) {
				if (PatternID[i] != pair.second->NodePatten[i]) {
					isCorrect = false;
					break;
				}
				isCorrect = true;
			}
			return pair.second;
		}
	}
	return nullptr;
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
