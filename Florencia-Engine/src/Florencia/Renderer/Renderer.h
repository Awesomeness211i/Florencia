#pragma once
#include <Renderer/Camera.h>
#include <Renderer/RenderAPI.h>

namespace Florencia {

	struct RenderData {
		
	};

	class Renderer {
	public:
		static void Init(void* window);
		static void Shutdown();

		static void SetClearColor(float r, float g, float b, float a = 1.0f);

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