#include "GraphicsContext.h"
#include <Florencia/Renderer/Renderer.h>
#include <Florencia/Renderer/OpenGL/OpenGLContext.h>

namespace Florencia {

	GraphicsContext* GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: return nullptr;
			//case RendererAPI::API::Metal: return new MetalContext(static_cast<*>(window));
			case RendererAPI::API::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(window));
			//case RendererAPI::API::Vulkan: return new VulkanContext(static_cast<*>(window));
			//case RendererAPI::API::DirectX11: return new DirectX11Context(static_cast<*>(window));
			//case RendererAPI::API::DirectX12: return new DirectX12Context(static_cast<*>(window));
			default: return nullptr;
		}
	}

}