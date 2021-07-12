module;
import Florencia;
#include <Florencia/Core/EntryPoint.h>
export module FloEditor;
import EditorLayer;
import Window;

export namespace Florencia {

	class FloEditor : public Application {
	public:
		FloEditor(const std::string& name, ApplicationCommandLineArgs args) : Application(name, args) {
			AddLayer(new EditorLayer());
		}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new FloEditor("FloEditor", args);
	}
}