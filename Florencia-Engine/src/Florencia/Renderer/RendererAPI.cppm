export module RendererAPI;
import FloMath;

export namespace Florencia {

	class RendererAPI {
	public:
		enum class API {
			DirectX11,
			DirectX12,
			OpenGL,
			Vulkan,
			Metal,
			None
		};
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		//virtual void SetViewport(Uint32 x, Uint32 y, Uint32 width, Uint32 height) = 0;
		virtual void SetClearColor(const FloMath::Vec4<float>& color) = 0;
		virtual void Clear() = 0;

		//virtual void DrawIndexed(const VertexArray& vertexArray, Uint32 count = 0) = 0;

		static API GetAPI() { return s_API; }
		static RendererAPI* Create();
	private:
		static API s_API;
	};

}