#include <Florencia.h>
#include <Florencia/Core/EntryPoint.h>

namespace Florencia {

	FLO_APPLICATION(FloEditor) {
	public:
		FLO_APP_CONSTRUCTOR(FloEditor) {
			
		}
	};

	Application* CreateApplication() {
		WindowProps m_Data;
		m_Data.Name = "FloEditor";
		m_Data.Width = 1080;
		m_Data.Height = 720;
		m_Data.VSync = true;
		m_Data.API = Renderer::API::DirectX11;
		return new FloEditor(m_Data);
	}
}