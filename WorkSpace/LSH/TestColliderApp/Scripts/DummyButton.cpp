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
