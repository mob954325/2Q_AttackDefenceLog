#include "EffectComponent.h"
#include "Resources/Loaders/SpriteSheetLoader.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void EffectComponent::OnCreate()
{
	circleouter = owner->AddComponent<BitmapRenderer>();
	circleouter->SetUseCustomRect(true);
	circleouter->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\circle_outer.png");

	circleinner = owner->AddComponent<BitmapRenderer>();
	circleinner->SetUseCustomRect(true);
	circleinner->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\circle_inner.png");

	linehorizon = owner->AddComponent<BitmapRenderer>();
	linehorizon->SetUseCustomRect(true);
	linehorizon->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\line_horizon.png");

	circleoutersize = circleouter->GetResource()->GetBitmap()->GetSize();
	circleinnersize = circleinner->GetResource()->GetBitmap()->GetSize();
	linehorizonsize = linehorizon->GetResource()->GetBitmap()->GetSize();
}

void EffectComponent::OnStart()
{

}

void EffectComponent::OnDestroy()
{

}

void EffectComponent::Update()
{
	
}

//크기와 투명도를 매개변수로 받음
void EffectComponent::Setcircleoutervalue(float scalevalue, float capacityvalue)
{
	circleouterDestRect.left = -scalevalue /2;
	circleouterDestRect.top = scalevalue / 2;
	circleouterDestRect.right = scalevalue / 2;
	circleouterDestRect.bottom = -scalevalue / 2;

	circleouterSrcRect.right = circleoutersize.width;
	circleouterSrcRect.bottom = circleoutersize.height;

	circleouter->SetCapacity(capacityvalue);

	circleouter->SetDestRect(circleouterDestRect);
	circleouter->SetSrcRect(circleouterSrcRect);
}

//크기와 투명도를 매개변수로 받음
void EffectComponent::Setcircleinnervalue(float scalevalue, float capacityvalue)
{
	circleinnerDestRect.left = -scalevalue / 2;
	circleinnerDestRect.top = scalevalue / 2;
	circleinnerDestRect.right = scalevalue / 2;
	circleinnerDestRect.bottom = -scalevalue / 2;

	circleinnerSrcRect.right = circleinnersize.width;
	circleinnerSrcRect.bottom = circleinnersize.height;

	circleinner->SetCapacity(capacityvalue);
	circleinner->SetDestRect(circleinnerDestRect);
	circleinner->SetSrcRect(circleinnerSrcRect);
}

// 너비, 높이의 값을 받음
void EffectComponent::Setlinehorizonvalue(float width, float height)
{
	float thiswidth = 0;
	float thisheight = 0;
	if (width <= 0) { 0; }
	else thiswidth = width;
	if (height == 0) { thisheight = linehorizonsize.height; }
	else thisheight = height;

	linehorizonDestRect.left = -thiswidth / 2;
	linehorizonDestRect.top = thisheight / 2;
	linehorizonDestRect.right = thiswidth / 2;
	linehorizonDestRect.bottom = -thisheight / 2;


	linehorizonSrcRect.right = linehorizonsize.width;
	linehorizonSrcRect.bottom = linehorizonsize.height;

	linehorizon->SetDestRect(linehorizonDestRect);
	linehorizon->SetSrcRect(linehorizonSrcRect);

}
