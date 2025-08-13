#include "StageDarknessImg.h"
#include "Components/Base/GameObject.h"
#include "Datas/EngineData.h"

void StageDarknessImg::OnCreate()
{
	darkness = owner->AddComponent<BitmapRenderer>();
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
}

void StageDarknessImg::OnStart()
{
}