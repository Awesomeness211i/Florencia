#include <Renderer/Renderer.h>
#include <Renderer/RenderAPI.h>

namespace Florencia {

	RenderAPI* Renderer::s_RenderAPI = RenderAPI::Create();

	void Renderer::Init() {
		if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->Init();
		}
	}

	void Renderer::Shutdown() {

	}

	void Renderer::SetClearColor() {
		if (RenderAPI::GetAPI() != RenderAPI::API::None) {
			s_RenderAPI->SetClearColor();
		}
	}

	void Renderer::BeginScene(Camera& camera) {

	}

	void Renderer::EndScene() {

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