#include "DummyButton.h"
#include "Components/Base/GameObject.h"

void DummyButton::OnCreate()
{
	button = owner->AddComponent<Button>();
}

void DummyButton::OnStart()
{
	D2D1_SIZE_F imageSize = button->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	button->SetRect(imageSize.width, imageSize.height);
	button->AddOnClickEvent(std::bind(&DummyButton::OnClick, this));
	button->AddOnClickEvent([&]() { SetValue(100); });
}

void DummyButton::OnUpdate()
{
	
}

void DummyButton::OnFixedUpdate()
{
	
}

void DummyButton::OnDestroy()
{
	
}

void DummyButton::OnClick()
{
	std::cout << "Button 클릭됨" << std::endl;
}

void DummyButton::SetValue(int value)
{
	std::cout << "클릭 전 value : " << this->value << std::endl;
	this->value = value;
	std::cout << "클릭 후 value : " << this->value << std::endl;
}