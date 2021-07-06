module;

import Florencia;
#include <Florencia/Core/EntryPoint.h>

export module FloEditor;
import EditorLayer;
import Window;

export namespace Florencia {

	class FloEditor : public Application {
	public:
		FloEditor(const WindowProps& props) : Application(props) {
			AddLayer(new EditorLayer());
		}

	};

	Application* CreateApplication() {
		WindowProps data("FloEditor", 1080, 720);
		return new FloEditor(data);
	}
}
