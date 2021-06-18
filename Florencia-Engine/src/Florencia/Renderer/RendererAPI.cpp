module;
#include <Florencia/Core/PlatformDetection.h>
module RendererAPI;
import DirectX11;
import DirectX12;
import Vulkan;
import OpenGL;
import Metal;

namespace Florencia {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	RendererAPI* RendererAPI::Create() {
		switch (s_API) {
			#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
			case RendererAPI::API::DirectX11: return new DirectX11();
			case RendererAPI::API::DirectX12: return new DirectX12();
			#elif defined(FLO_PLATFORM_MACOS)
			case RendererAPI::API::Metal: return new Metal();
			#endif
			case RendererAPI::API::Vulkan: return new Vulkan();
			case RendererAPI::API::OpenGL: return new OpenGL();
			case RendererAPI::API::None: return nullptr;
		}
		return nullptr;
	}

}