#pragma once
#include <Florencia/Renderer/RendererAPI.h>

namespace Florencia {

	class Vulkan : public RendererAPI {
	public:
		Vulkan();

		void Init() override;

		void Clear() override;
		void SetClearColor(const FloMath::Vec4<float>& color) override;
	private:

	};

}
