#pragma once
#include <Florencia/Renderer/RendererAPI.h>

namespace Florencia {

	class DirectX12 : public RendererAPI {
	public:
		DirectX12();

		void Init() override;

		void Clear() override;
		void SetClearColor(const FloMath::Vec4<float>& color) override;
	private:

	};

}
