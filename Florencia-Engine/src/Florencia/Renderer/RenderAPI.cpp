#include "RenderAPI.h"

#include <Renderer/Directx/12/DirectX12.h>
#include <Renderer/Directx/11/DirectX11.h>
#include <Renderer/Vulkan/Vulkan.h>
#include <Renderer/OpenGL/OpenGL.h>
#include <Renderer/Metal/Metal.h>

namespace Florencia {

	RenderAPI::API RenderAPI::s_API = RenderAPI::API::DirectX11;

	RenderAPI* RenderAPI::Create() {
		switch (s_API) {
			case RenderAPI::API::None: return nullptr;
			case RenderAPI::API::Metal: return new Metal();
			case RenderAPI::API::OpenGL: return new OpenGL();
			case RenderAPI::API::Vulkan: return new Vulkan();
			case RenderAPI::API::DirectX11: return new DirectX11();
			case RenderAPI::API::DirectX12: return new DirectX12();
		}
		return nullptr;
	}

}