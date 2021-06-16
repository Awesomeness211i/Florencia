import Florencia;
import EditorLayer;
#include <Florencia/Core/EntryPoint.h>

namespace Florencia {

	class FloEditor : public Application {
	public:
		FloEditor(const WindowProps& props) : Application(props) {
			AddLayer(new EditorLayer(m_EventHandler));
		}

	};

	Application* CreateApplication() {
		WindowProps m_Data("FloEditor", 1080, 720);
		return new FloEditor(m_Data);
	}
}
