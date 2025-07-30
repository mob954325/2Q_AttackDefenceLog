#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"


	class Node : public MonoBehavior
	{
	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;

	protected:
		BitmapRenderer* bitmapRenderer{};
		std::shared_ptr<BitmapResource> stampBitmap = nullptr;
	};

