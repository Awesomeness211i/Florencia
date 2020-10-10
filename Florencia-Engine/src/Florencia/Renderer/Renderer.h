#pragma once
#include <Renderer/Camera.h>
#include <Renderer/RenderAPI.h>

namespace Florencia {

	struct RenderData {
		
	};

	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor();

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const RenderData& data);

		static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		static void Clear();
		static void SetViewport();
		static void DrawIndexed();

		static RenderAPI* s_RenderAPI;
	};

}