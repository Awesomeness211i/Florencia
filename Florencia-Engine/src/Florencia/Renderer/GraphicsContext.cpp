module GraphicsContext;
import DirectX11Context;
import DirectX12Context;
import MetalContext;
import OpenGLContext;
import VulkanContext;
import Window;

namespace Florencia {

	GraphicsContext* GraphicsContext::Create(Window* window, bool vsync) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLContext(window, vsync);
			case RendererAPI::API::Vulkan: return new VulkanContext(window, vsync);
			case RendererAPI::API::DirectX11: return new DirectX11Context(window, vsync);
			case RendererAPI::API::DirectX12: return new DirectX12Context(window, vsync);
			case RendererAPI::API::Metal: return new MetalContext(window, vsync);
		}
		return nullptr;
	}

}