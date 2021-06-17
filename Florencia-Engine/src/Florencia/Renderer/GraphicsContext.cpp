module GraphicsContext;
import DirectX11Context;
import DirectX12Context;
import MetalContext;
import OpenGLContext;
import VulkanContext;

namespace Florencia {

	GraphicsContext* GraphicsContext::Create(void* window, bool vsync) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLContext(nullptr, vsync);
			case RendererAPI::API::Vulkan: return new VulkanContext(nullptr, vsync);
			case RendererAPI::API::DirectX11: return new DirectX11Context(nullptr, vsync);
			case RendererAPI::API::DirectX12: return new DirectX12Context(nullptr, vsync);
			case RendererAPI::API::Metal: return new MetalContext(nullptr, vsync);
		}
		return nullptr;
	}

}