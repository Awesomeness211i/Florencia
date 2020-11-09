#pragma once

namespace Florencia {

	class RenderAPI {
	public:
		enum class API {
			DirectX11,
			DirectX12,
			OpenGL,
			Vulkan,
			Metal,
			None
		};
		virtual ~RenderAPI() = default;

		virtual void Init(void* window) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;

		static API GetAPI() { return s_API; }
		static RenderAPI* Create();
	private:
		static API s_API;
	};

}