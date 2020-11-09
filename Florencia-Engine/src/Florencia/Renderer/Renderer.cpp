#include <Renderer/Renderer.h>
#include <Renderer/RenderAPI.h>

namespace Florencia {

	RenderAPI* Renderer::s_RenderAPI = RenderAPI::Create();

	void Renderer::Init(void* window) {
		if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->Init(window);
		}
	}

	void Renderer::Shutdown() {

	}

	void Renderer::SetClearColor(float r, float g, float b, float a) {
		if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->SetClearColor(r, g, b, a);
		}
	}

	void Renderer::BeginScene(Camera& camera) {

	}

	void Renderer::EndScene() {
		Clear();
	}

	void Renderer::Submit(const RenderData& data) {

	}

	void Renderer::Clear() {
		if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->Clear();
		}
	}

	void Renderer::SetViewport() {
		/*if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->SetViewport();
		}*/
	}

	void Renderer::DrawIndexed() {
		/*if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->DrawIndexed();
		}*/
	}

}