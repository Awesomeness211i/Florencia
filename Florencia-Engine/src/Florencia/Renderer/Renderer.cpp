#include "Renderer.h"
#include <Renderer/None/NoRenderer.h>
#include <Renderer/OpenGL/OpenGL.h>

#include <Platform/Platform.h>
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
	#include <Renderer/DirectX/DirectX12.h>
	#include <Renderer/DirectX/DirectX11.h>
	#include <Renderer/Vulkan/Vulkan.h>
#elif defined(FLO_PLATFORM_MACOS)
	#include <Renderer/Metal/Metal.h>
	#include <Renderer/Vulkan/Vulkan.h>
#endif

namespace Florencia {

	Renderer::Renderer(API api) {
		m_Api = api;
	}

	Renderer* Renderer::Create(API api) {
		switch (api) {
			#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
			case Renderer::API::DirectX11: return new DirectX11(api);
			case Renderer::API::DirectX12: return new DirectX12(api);
			case Renderer::API::Vulkan: return new Vulkan(api);
			#elif defined(FLO_PLATFORM_MACOS)
			case Renderer::API::Vulkan: return new Vulkan(api);
			case Renderer::API::Metal: return new Metal(api);
			#endif
			case Renderer::API::OpenGL: return new OpenGL(api);
			case Renderer::API::None: return new NoRenderer(api);
		}
		return nullptr;
	}

}