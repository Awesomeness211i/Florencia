#pragma once
#include <Renderer/RenderAPI.h>

namespace Florencia {

	class DirectX12 : public RenderAPI {
	public:
		void Init() override;
		void Clear() override;
		void SetClearColor() override;
	private:

	};

}