# StatComponent

---

## 설명

int 형 변수를 delegate를 사용할 수 있도록 래핑한 컴포넌트

## 예시 코드

### 멤버 함수

| 이름 | 내용 |
| --- | --- |
| GetValue | statValue를 반환하는 함수  |
| GetValueFunctionObject | ChangeState를 delegate의 이벤트로 받기 위한 객체 반환 함수 |
| ChangeStat | statValue의 값을 변경하는 함수 |

### 멤버 변수

### private

| 이름 | 내용 |
| --- | --- |
| statValue | int형 데이터 |