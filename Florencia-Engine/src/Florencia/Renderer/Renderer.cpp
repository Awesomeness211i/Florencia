#include "Renderer.h"

#include <Renderer/DirectX/DirectX12.h>
#include <Renderer/DirectX/DirectX11.h>
#include <Renderer/Vulkan/Vulkan.h>
#include <Renderer/OpenGL/OpenGL.h>
#include <Renderer/Metal/Metal.h>

namespace Florencia {

	Renderer* Renderer::Create(API api) {
		switch (api) {
			case Renderer::API::None: return nullptr;
			case Renderer::API::Metal: return new Metal();
			case Renderer::API::OpenGL: return new OpenGL();
			case Renderer::API::Vulkan: return new Vulkan();
			case Renderer::API::DirectX11: return new DirectX11();
			case Renderer::API::DirectX12: return new DirectX12();
		}
		return nullptr;
	}

}