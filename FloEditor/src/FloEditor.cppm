module;
import Florencia;
#include <Florencia/Core/EntryPoint.h>

export module FloEditor;
import EditorLayer;

export namespace Florencia {

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
