#pragma once
#include <Renderer/Renderer.h>

namespace Florencia {

	class DirectX12 : public Renderer {
	public:
		void Init(void* window) override;
		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:

	};

}