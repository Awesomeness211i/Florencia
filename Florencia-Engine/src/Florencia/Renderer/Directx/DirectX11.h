#pragma once
#include <Renderer/RenderAPI.h>

namespace Florencia {

	class DirectX11 : public RenderAPI {
	public:
		void Init() override;
		void Clear() override;
		void SetClearColor() override;
	private:

	};

}