# FSMInstance

---

ScriptComponent에서 파생됨

## 설명

AnimatorController를 기반으로 FSM업데이트를 하는 컴포넌트

## 예시 코드

### 멤버 함수

### public

| 이름 | 내용 |
| --- | --- |
| EvaluateConditions | 이번 프레임의 컨디션 변화를 확인하는 함수 |
| SetAnimationController | 해당 클래스에 AnimationController를 추가하는 함수 |
| SetStateBehavior | 정의한 IStateBehaviorBase를 이름으로 추가하는 함수 |
| GetInt | 파라미터의 int값을 가져오는 함수 |
| SetInt | 파라미터의 int값을 설정하는 함수 |
| GetBool | 파라미터의 bool값을 가져오는 함수 |
| SetBool | 파라미터의 bool값을 설정하는 함수 |
| GetFloat | 파라미터의 float값을 가져오는 함수 |
| SetFloat | 파라미터의 float값을 설정하는 함수 |
| GetTrigger | 파라미터의 trigger값을 가져오는 함수 |
| SetTrigger | 파라미터의 trigger값을 설정하는 함수 |
| IsParameterChanged | Condition의 파라미터가 모두 변경되었는지 확인하는 함수 |

### private

| 이름 | 내용 |
| --- | --- |
| RegisterIntParameters | AnimationController의 int형 파라미터를 등록하는 함수 |
| RegisterFloatParameters | AnimationController의 float형 파라미터를 등록하는 함수 |
| RegisterBoolParameters | AnimationController의 bool형 파라미터를 등록하는 함수 |
| RegisterTriggerParameters | AnimationController의 trigger형 파라미터를 등록하는 함수 |
| ChangeState | 매개변수 이름의 상태로 변경하는 함수 |
| ResetTrigger | 상태 변경 후나 프레임 끝나고 실행, 모든 트리거 변수를 false로 변경하는 함수 |
| StartStateBehavior | IStateBehaviorBase의 Start를 실행하는 함수 |
| UpdateStateBehavior | IStateBehaviorBase의 Update를 실행하는 함수 |
| ExitStateBehavior | IStateBehaviorBase의 Exit를 실행하는 함수 |

### 멤버 변수

### private

| 이름 | 내용 |
| --- | --- |
| controller | AnimatorController 참조하는 변수 |
| currentStateIndex | 현재 실행 중인 상태의 인덱스를 저장하는 변수 |
| prevStateIndex | 이전에 실행했던 상태의 인덱스를 저장하는 변수 |
| elapsedTime | 현재 상태에서 지난 시간입니다. 상태의 최대 시간이 되면 0으로 초기화됩니다. |
| stateBehavitors | 각 인덱스에 대입되는 상태에 따른 추가 행동을 정의한 클래스 컨테이너 |
| intParams | AnimatorController의 int형 파라미터 모음 |
| floatParams | AnimatorController의 float 파라미터 모음 |
| boolParams | AnimatorController의 bool 파라미터 모음 |
| triggerParams | AnimatorController의 trigger 파라미터 모음 |