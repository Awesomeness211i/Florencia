#pragma once
#include <Renderer/Renderer.h>

namespace Florencia {

	//Test Functions for now
	class DirectX11 : public Renderer {
	public:
		DirectX11(API api);

		void Init(void* window) override;

		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:

	};

}
