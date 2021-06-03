#pragma once
#include <Florencia/Renderer/GraphicsContext.h>

namespace Florencia {

	class DirectX12Context : public GraphicsContext {
	public:
		DirectX12Context(void* window, bool vsync);

		void Init() override;
		void SwapBuffers() override;
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
	private:
		void* m_WindowHandle;
		bool m_Vsync;
	};

}