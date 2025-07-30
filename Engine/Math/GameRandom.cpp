#include "GameRandom.h"
#include <random>
#include <cmath> 
#include <utility> 

float GameRandom::RandomRange(float min, float max)
{
	static std::random_device rd;	// seed 
	static std::mt19937 gen(rd());	// Mersenne Twister 알고리즘 기반 난수 생성기 사용 rd()로 초기화
	std::uniform_real_distribution<float> dist(min, max); // 균등 분포(uniform distribution) 를 사용해 float 범위의 난수를 생성할 수 있도록 해주는 객체.
	return dist(gen);	// gen 난수 생성기와 dist 분포를 조합해서 float 난수 생성
}

Vector2 GameRandom::RandomInsideUnitCircle()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist01(0.0f, 1.0f);
    std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.1415926535);

    float angle = distAngle(gen);
    float radius = std::sqrt(dist01(gen)); // sqrt로 균등하게 분포

    float x = radius * std::cos(angle);
    float y = radius * std::sin(angle);

    return { x, y };
}
