#pragma once
#include <Florencia/Renderer/RendererAPI.h>

namespace Florencia {

	class OpenGL : public RendererAPI {
	public:
		OpenGL();

		void Init() override;

		void Clear() override;
		void SetClearColor(const FloMath::Vec4<float>& color) override;
	private:
		
	};

}
