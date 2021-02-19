#pragma once
#include <Renderer/SwapChain.h>

namespace Florencia {

	//Going to be how I use the swapchain
	class DX11SwapChain : public SwapChain {
	public:
		DX11SwapChain();
		void Present() override;
	private:
		IDXGISwapChain* pSwapChain;
	};

}
