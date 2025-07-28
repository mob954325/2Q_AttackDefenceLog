# Scene 만들기 및 GameObject 추가

---

모든 Scene은 Scene클래스를 상속받아서 가상함수인 OnEnterImpl(), OnExitImpl(), OnUpdateImpl()를 정의하면 됩니다.

해당 클래스는 에디터의 hierachy역할을 합니다. 

사용 목적은 Enter에 게임오브젝트 생성, 추가될 ScoreManager등 추가 되면 Update에서 사용할 수 있을겁니다.

## 예시 코드

### MenuScene.h

```cpp
class MenuScene : public Scene
{
	protected:
		void OnEnterImpl() override;
		void OnExitImpl() override;
		void UpdateImpl() override;

	private:
		GameObject* menuObj;
};
```

### MenuScene.cpp

```cpp
void MenuScene::OnEnterImpl()
{
	menuObj = new GameObject(); // GameObject 객체 생성
	menuObj->AddComponent<MenuTextObject>(); // MonoBehaivor 등록
	AddGameObject(menuObj);	// Scene에 GameObject 추가
}

void MenuScene::OnExitImpl()
{
}

void MenuScene::UpdateImpl()
{
}
```