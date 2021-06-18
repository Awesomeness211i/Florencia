export module RenderCommand;
import RendererAPI;
import FloMath;

export namespace Florencia {

	class RenderCommand {
	public:

		static void Init() { if (s_RendererAPI) { s_RendererAPI->Init(); } }

		//static void SetViewport(Uint32 x, Uint32 y, Uint32 width, Uint32 height) { if (s_RendererAPI) { s_RendererAPI.SetViewport(x, y, width, height); } }

		static void SetClearColor(const FloMath::Vec4<float>& color) { if (s_RendererAPI) { s_RendererAPI->SetClearColor(color); } }

		static void Clear() { if (s_RendererAPI) { s_RendererAPI->Clear(); } }

		//static void DrawIndexed(const Ref<VertexArray>& vertexArray, Uint32 count = 0) { if (s_RendererAPI) { s_RendererAPI->DrawIndexed(vertexArray, count); } }

	private:
		static RendererAPI* s_RendererAPI;
	};

	RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

}