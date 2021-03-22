#pragma once
#include <Renderer/RendererAPI.h>

namespace Florencia {

	//Test Functions for now
	class DirectX11 : public RendererAPI {
	public:
		DirectX11();

		void Init() override;

		void Clear() override;
		void SetClearColor(const FloMath::Vec4<float>& color) override;
	private:

	};

}
