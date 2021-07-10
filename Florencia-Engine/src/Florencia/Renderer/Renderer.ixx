module;
#include <stdint.h>
export module Renderer;
import RenderCommand;
import RendererAPI;
import FloMath;

namespace Florencia {

	export class Renderer {
	public:
		static void Init() { RenderCommand::Init(); }
		static void Shutdown() { /*Renderer2D::Shutdown();*/ }

		static void OnWindowResize(uint32_t width, uint32_t height) { /*RenderCommand::SetViewport(0, 0, width, height)*/ }

		static void BeginScene() { /*s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();*/ }
		static void EndScene() {}

		//static void Submit(const Shader& shader, const VertexArray& vertexArray, const FloMath::Mat4<float>& transform) {}

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}