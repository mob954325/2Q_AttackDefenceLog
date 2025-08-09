#include "EffectObject.h"
#include "Resources/Loaders/SpriteSheetLoader.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void EffectObject::OnUpdate()
{

}

void EffectObject::OnCreate()
{
	Effect = owner->AddComponent<BitmapRenderer>();
	Effect->SetUseCustomRect(true);
	Effect->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/circle_outer.png");
	Effectsize = Effect->GetResource()->GetBitmap()->GetSize();
}

void EffectObject::OnStart()
{

}

void EffectObject::OnDestroy()
{

}

void EffectObject::SetEffectValue(float width, float height, float capacityvalue, bool checkend)
{
	if(checkend){
	EffectDestRect.left = -width / 2;
	EffectDestRect.top = height / 2;
	EffectDestRect.right = width / 2;
	EffectDestRect.bottom = -height / 2;

	EffectSrcRect.right = Effectsize.width;
	EffectSrcRect.bottom = Effectsize.height;

	Effect->SetCapacity(capacityvalue);
	Effect->SetDestRect(EffectDestRect);
	Effect->SetSrcRect(EffectSrcRect);
	}
	else
	{
		EffectDestRect.top = 0;
		EffectDestRect.right = 0;
		EffectDestRect.bottom = 0;

		EffectSrcRect.right = 0;
		EffectSrcRect.bottom = 0;

		Effect->SetCapacity(0);
		Effect->SetDestRect(EffectDestRect);
		Effect->SetSrcRect(EffectSrcRect);
	}
}

void EffectObject::SetOwnerPosition(float x, float y)
{
	owner->GetTransform().SetPosition(x, y);
}

void EffectObject::SetImage(std::wstring path)
{
	Effect->CreateBitmapResource(path);
	Effectsize = Effect->GetResource()->GetBitmap()->GetSize();
}

void EffectObject::SetLayer(int value)
{
	Effect->SetOrderInLayer(value);
}
