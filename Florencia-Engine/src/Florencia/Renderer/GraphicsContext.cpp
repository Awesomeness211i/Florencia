#include "GraphicsContext.h"

#include <Florencia/Core/PlatformDetection.h>
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
#include <Florencia/Renderer/DirectX11/DirectX11Context.h>
#include <Florencia/Renderer/DirectX12/DirectX12Context.h>
#elif defined(FLO_PLATFORM_MACOS)
#include <Florencia/Renderer/Metal/MetalContext.h>
#endif

#include <Florencia/Renderer/Renderer.h>
#include <Florencia/Renderer/Vulkan/VulkanContext.h>
#include <Florencia/Renderer/OpenGL/OpenGLContext.h>

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