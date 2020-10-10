#pragma once
#include <Renderer/Renderer.h>

namespace Florencia {

	class Metal : public RenderAPI {
	public:
		void Init() override;
		void Clear() override;
		void SetClearColor() override;
	private:

	};

}