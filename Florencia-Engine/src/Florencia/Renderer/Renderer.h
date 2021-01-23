#pragma once

namespace Florencia {

	class Renderer {
	public:
		enum class API {
			DirectX11,
			DirectX12,
			OpenGL,
			Vulkan,
			Metal,
			None
		};
		virtual ~Renderer() = default;

		virtual void Init(void* window) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;

		API GetAPI() { return m_Api; }
		Renderer* Create(API api);
	protected:
		API m_Api;
	};

}