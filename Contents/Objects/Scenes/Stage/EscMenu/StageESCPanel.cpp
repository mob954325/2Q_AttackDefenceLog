#include "StageESCPanel.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"

void StageESCPanel::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	barBitmap = owner->AddComponent<BitmapRenderer>();

	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetPosition(0, EngineData::SceenHeight * 0.3f);
}

void StageESCPanel::OnStart()
{
	barBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\MenuUI\\esc_menu_ui_bar.png");
	DisablePanel();
}

void StageESCPanel::OnUpdate()
{
	if (input->IsKeyPressed(VK_ESCAPE))
	{
		if (buttons.empty()) return;

		DisablePanel();
	}
}

void StageESCPanel::SetButtons(const std::vector<GameObject*> buttons)
{
	this->buttons = buttons;
	auto comp = this->buttons[0]->GetComponent<Button>();

	if (comp)
	{
		comp->AddOnClickEvent([&]() {DisablePanel(); });
	}
}

void StageESCPanel::SetButtonsPosition()
{
	int size = buttons.size();
	int startX = EngineData::SceenWidth * 0.3f;
	Vector2 ownerPos = owner->GetTransform().GetPosition();
	float gap = 250.0f;

	for (int i = 0; i < size; i++)
	{
		buttons[i]->GetTransform().SetPosition(startX + gap * i, ownerPos.y);
	}
}

void StageESCPanel::DisablePanel()
{
	int size = buttons.size();
	for (int i = 0; i < size; i++)
	{
		auto comp = buttons[i]->GetComponent<Button>();
		comp->DisableBitmaps();
		comp->SetActive((comp->IsActiveSelf() ? false : true));
	}

	barBitmap->SetActive(barBitmap->IsActiveSelf() ? false : true);
}