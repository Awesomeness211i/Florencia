#include <d3d11_4.h>
#include <wrl.h>

#include "DirectX11.h"

namespace Florencia {

	void DirectX11::Init(void* window) {
		m_api = Renderer::API::DirectX11;
		DXGI_SWAP_CHAIN_DESC swapdescriptor = {};
		swapdescriptor.BufferDesc.Width = 0;
		swapdescriptor.BufferDesc.Height = 0;
		swapdescriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapdescriptor.BufferDesc.RefreshRate.Numerator = 0;
		swapdescriptor.BufferDesc.RefreshRate.Denominator = 0;
		swapdescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapdescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapdescriptor.SampleDesc.Count = 1;
		swapdescriptor.SampleDesc.Quality = 0;
		swapdescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapdescriptor.BufferCount = 1;
		swapdescriptor.OutputWindow = (HWND)window;
		swapdescriptor.Windowed = TRUE;
		swapdescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapdescriptor.Flags = 0;
		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, 0,
			nullptr, 0,
			D3D11_SDK_VERSION, &swapdescriptor,
			&pSwapChain, &pDevice,
			nullptr, &pContext);
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);
	}

	void DirectX11::Clear() {
		pSwapChain->Present(0u, 0u);
	}

	void DirectX11::SetClearColor(float r, float g, float b, float a) {
		const float color[] = { r, g, b, a };
		pContext->ClearRenderTargetView(pTarget, color);
	}

}