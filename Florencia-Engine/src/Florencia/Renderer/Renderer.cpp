module;
#include <Florencia/Math/FloMath.h>
module Renderer;
import RenderCommand;

namespace Florencia {

	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::Shutdown() {
		//Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		//RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene() {
		//s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	/*void Submit(const Shader& shader, const VertexArray& vertexArray, const FloMath::Mat4<float>& transform) {

	}*/

}