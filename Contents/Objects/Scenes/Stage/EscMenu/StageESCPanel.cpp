#include "StageESCPanel.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"
#include "Scripts/GameManager.h"
#include "EscMuteButton.h"

void StageESCPanel::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	owner->GetTransform().SetUnityCoords(false);
	barBitmap = owner->AddComponent<BitmapRenderer>();

	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetPosition(0, EngineData::SceenHeight * 0.3f);
}

void StageESCPanel::OnStart()
{
	barBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\MenuUI\\esc_menu_ui_bar.png");
	int size = buttons.size();
	for (int i = 0; i < size; i++)
	{
		auto comp = buttons[i]->GetComponent<Button>();
		comp->DisableBitmaps();
		comp->SetActive(false);
	}

	barBitmap->SetActive(false);
}

void StageESCPanel::OnUpdate()
{
	if (!isInputEnable) return;

	if (input->IsKeyPressed(VK_ESCAPE))
	{
		if (buttons.empty()) return;

		if (buttons[2]->GetComponent<EscMuteButton>()->GetSoundMutePanel()->IsOpen())
		{
			buttons[2]->GetComponent<EscMuteButton>()->GetSoundMutePanel()->SetOpen(false);

			int size = buttons.size();
			for (int i = 0; i < size; i++)
			{
				auto comp = buttons[i]->GetComponent<Button>();
				comp->DisableBitmaps();
				comp->SetActive(true);
			}

		}
		else // esc 처리
		{
			bool isActive = barBitmap->IsActiveSelf();
			if (isActive)
			{
				DisablePanel();
			}
			else
			{
				EnablePanel();
			}
		}
	}
}

void StageESCPanel::SetButtons(const std::vector<GameObject*> buttons)
{
	this->buttons = buttons;

	if (buttons.empty()) return;

	auto button0 = this->buttons[0]->GetComponent<Button>();
	button0->AddOnClickEvent([&]() 
		{ 
			if(!this->buttons[2]->GetComponent<EscMuteButton>()->GetSoundMutePanel()->IsOpen())
			{
				DisablePanel(); 
			}
		});

	auto button1 = this->buttons[1]->GetComponent<Button>();
	button1->AddOnClickEvent([&]()
		{
			if (!this->buttons[2]->GetComponent<EscMuteButton>()->GetSoundMutePanel()->IsOpen())
			{
				Singleton<SceneManager>::GetInstance().LoadScene(1);
			}
		});

	auto button2 = this->buttons[2]->GetComponent<Button>();
	button2->AddOnClickEvent([&]() 
		{ 
			auto comp = this->buttons[2]->GetComponent<EscMuteButton>();
			if (!comp->GetSoundMutePanel()->IsOpen())
			{
				comp->GetSoundMutePanel()->SetOpen(true);

				int size = this->buttons.size();
				for (int i = 0; i < size; i++)
				{
					auto comp = this->buttons[i]->GetComponent<Button>();
					comp->DisableBitmaps();
					comp->SetActive(false);
				}
			}
		});
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
		comp->SetActive(false);
	}

	Singleton<GameManager>::GetInstance().SetGameState(GameState::Play);
	barBitmap->SetActive(false);
}

void StageESCPanel::EnablePanel()
{
	int size = buttons.size();
	for (int i = 0; i < size; i++)
	{
		auto comp = buttons[i]->GetComponent<Button>();
		comp->DisableBitmaps();
		comp->SetActive(true);
	}

	Singleton<GameManager>::GetInstance().SetGameState(GameState::Pause);
	barBitmap->SetActive(true);
}

void StageESCPanel::SetInputEnable(bool value)
{
	isInputEnable = value;
}
