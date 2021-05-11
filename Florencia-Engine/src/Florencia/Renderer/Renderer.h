#pragma once
#include "RendererAPI.h"

namespace Florencia {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(Uint32 width, Uint32 height);

		static void BeginScene();
		static void EndScene();

		//static void Submit(const Shader& shader, const VertexArray& vertexArray, const FloMath::Mat4<float>& transform);
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}