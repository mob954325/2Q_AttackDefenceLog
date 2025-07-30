# Vector2

---

경로 : /Math/Vector2

## 설명

2차원 정보값을 담고있는 구조체

## 예시 코드

```cpp
void DummyButton::OnStart()
{
	Vector2 start = Vector2::Zero(); // start = { 0, 0 };
	Vector2 end = { 2,3 };           
	Vector2 dir = (end - start).Normalize(); // end - start의 방향 벡터
}
```

### 멤버 함수

| 이름 | 내용 |
| --- | --- |
| IsZero | vector의 값이 0.0인지 확인하는 함수 |
| Dot | dot product 연산을 수행하는 함수 |
| Lerp | vector 선형보간을 연산하는 함수 |
| Megnituede | 길이를 반환하는 함수 |
| SqrMegnitude | 길이의 제곱 값을 반환하는 함수 |
| Normalize | 벡터 정규화 함수 |

### Static 함수

| 이름 | 내용 |
| --- | --- |
| Down | { 0.0, -1.0 } 을 반환 |
| Left | { -1.0, 0.0 } 을 반환 |
| One | { 1.0, 1.0 } 을 반환 |
| Right | { 1.0, 0.0 } 을 반환 |
| Up | { 0.0, 1.0 } 을 반환 |
| Zero | { 0.0, 0.0 } 을 반환 |

### 연산자

| 이름 | 내용 |
| --- | --- |
| operator-() | 음수 부호 |
| operator+ | 더하기 연산 |
| operator- | 빼기 연산 |
| operator* | 곱하기 연산 |
| operator/ | 나누기 연산 |
|  operator+= | += 연산 |
| operator-= | -= 연산 |
| operator<< | 출력 시  “x, y” 형태로 출력함 |

### 멤버 변수

| 이름 | 내용 |
| --- | --- |
| x | 값 x |
| y | 값 y |