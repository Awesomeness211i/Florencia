module;
#include <Florencia/Core/PlatformDetection.h>
module GraphicsContext;
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
import DirectX11Context;
import DirectX12Context;
#elif defined(FLO_PLATFORM_MACOS)
import MetalContext;
#endif
import OpenGLContext;
import VulkanContext;
import Renderer;

namespace Florencia {

	GraphicsContext* GraphicsContext::Create(void* window, bool vsync) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLContext(nullptr, vsync);
			case RendererAPI::API::Vulkan: return new VulkanContext(nullptr, vsync);
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
			case RendererAPI::API::DirectX11: return new DirectX11Context(nullptr, vsync);
			case RendererAPI::API::DirectX12: return new DirectX12Context(nullptr, vsync);
		#elif defined(FLO_PLATFORM_MACOS)
			case RendererAPI::API::Metal: return new MetalContext(nullptr, vsync);
		#endif
		}
		return nullptr;
	}

}