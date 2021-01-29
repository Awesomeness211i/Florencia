#include <wrl.h>
#include "DirectX11.h"

namespace Florencia {
	DirectX11::DirectX11(API api) : Renderer(api) {
		descriptor.Flags = 0;
		descriptor.BufferCount = 1;
		descriptor.Windowed = TRUE;
		descriptor.SampleDesc.Count = 1;
		descriptor.BufferDesc.Width = 0;
		descriptor.BufferDesc.Height = 0;
		descriptor.SampleDesc.Quality = 0;
		descriptor.BufferDesc.RefreshRate.Numerator = 0;
		descriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		descriptor.BufferDesc.RefreshRate.Denominator = 0;
		descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		descriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		descriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	}

	void DirectX11::Init(void* window) {
		descriptor.OutputWindow = (HWND)window;
		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, 
			&descriptor, &pSwapChain, &pDevice, nullptr, &pContext
		);
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