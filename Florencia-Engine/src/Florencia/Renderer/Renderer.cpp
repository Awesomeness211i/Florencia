#include "Renderer.h"
#include "Vulkan/Vulkan.h"
#include "OpenGL/OpenGL.h"
#include "None/NoRenderer.h"

#include <Platform/Platform.h>
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
	#include "DirectX/DirectX12.h"
	#include "DirectX/DirectX11.h"
#elif defined(FLO_PLATFORM_MACOS)
	#include "Metal/Metal.h"
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
			#elif defined(FLO_PLATFORM_MACOS)
			case Renderer::API::Metal: return new Metal(api);
			#endif
			case Renderer::API::Vulkan: return new Vulkan(api);
			case Renderer::API::OpenGL: return new OpenGL(api);
			case Renderer::API::None: return new NoRenderer(api);
		}
		return nullptr;
	}

}
