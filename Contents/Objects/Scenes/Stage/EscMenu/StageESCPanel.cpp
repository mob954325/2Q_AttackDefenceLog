#include "StageESCPanel.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"
#include "Scripts/GameManager.h"
#include "EscMuteButton.h"
#include "Systems/AudioSystem.h"

void StageESCPanel::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);

	owner->GetTransform().SetUnityCoords(false);
	barBitmap = owner->AddComponent<BitmapRenderer>();

	input = owner->AddComponent<InputSystem>();

	owner->GetTransform().SetPosition(0, EngineData::SceenHeight * 0.3f);

	backgroundBitmap = owner->AddComponent<BitmapRenderer>();
}

void StageESCPanel::OnStart()
{
	backgroundBitmap->SetOrderInLayer(2000);
	barBitmap->SetOrderInLayer(2100);

	backgroundBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_back.png");
	backgroundBitmap->SetCapacity(0.5f);
	backgroundBitmap->SetUseCustomRect(true);

	D2D1_RECT_F destRect = { 0.0f, -EngineData::SceenHeight * 0.3f, EngineData::SceenWidth, EngineData::SceenHeight - EngineData::SceenHeight * 0.3f };
	backgroundBitmap->SetDestRect(destRect);
	D2D1_SIZE_F backgroundSize = backgroundBitmap->GetResource()->GetBitmap()->GetSize();
	D2D1_RECT_F srcRect = { 0.0f, 0.0f, backgroundSize.width, backgroundSize.height};
	backgroundBitmap->SetSrcRect(srcRect);

	barBitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\EscUI\\esc_menu_ui_bar.png");
	int size = buttons.size();
	for (int i = 0; i < size; i++)
	{
		auto comp = buttons[i]->GetComponent<Button>();
		comp->DisableBitmaps();
		comp->SetActive(false);
	}

	barBitmap->SetActive(false);
	backgroundBitmap->SetActive(false);
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
				Singleton<AudioSystem>::GetInstance().AgainstSound();
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
	backgroundBitmap->SetActive(false);
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
	backgroundBitmap->SetActive(true);
}

void StageESCPanel::SetInputEnable(bool value)
{
	isInputEnable = value;
}
