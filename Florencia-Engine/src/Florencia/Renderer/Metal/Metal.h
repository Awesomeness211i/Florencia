#pragma once
#include <Renderer/Renderer.h>

namespace Florencia {

	class Metal : public RenderAPI {
	public:
		void Init(void* window) override;
		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:

	};

}