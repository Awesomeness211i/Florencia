#include "RendererAPI.h"
#include "Vulkan/Vulkan.h"
#include "OpenGL/OpenGL.h"

#include <Florencia/Core/PlatformDetection.h>
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
#include "DirectX/DirectX12.h"
#include "DirectX/DirectX11.h"
#elif defined(FLO_PLATFORM_MACOS)
#include "Metal/Metal.h"
#endif

namespace Florencia {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

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