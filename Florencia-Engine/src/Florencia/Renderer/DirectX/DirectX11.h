#pragma once
#include <d3d11_4.h>
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
		DXGI_SWAP_CHAIN_DESC descriptor;
		ID3D11Device* pDevice = nullptr;
		IDXGISwapChain* pSwapChain = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
		ID3D11RenderTargetView* pTarget = nullptr;
	};

}