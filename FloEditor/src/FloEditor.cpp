#include <Florencia.h>

namespace Florencia {

	FLO_APPLICATION(FloEditor) {
	public:
		FloEditor(const WindowProps& props) : Application(props) {
			
		}

	};

	Application* CreateApplication() {
		WindowProps m_Data("FloEditor", 1080, 720);
		return new FloEditor(m_Data);
	}
}
