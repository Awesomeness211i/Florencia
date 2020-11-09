#pragma once
#include <Renderer/RenderAPI.h>

#include "DX11SwapChain.h"

namespace Florencia {

	//Test Functions for now
	class DirectX11 : public RenderAPI {
	public:
		void Init(void* window) override;
		void Clear() override;
		void SetClearColor(float r, float g, float b, float a) override;
	private:
		ID3D11Device* pDevice;
		IDXGISwapChain* pSwapChain;
		ID3D11DeviceContext* pContext;
		ID3D11RenderTargetView* pTarget;
	};

}