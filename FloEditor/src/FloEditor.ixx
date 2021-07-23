module;
#include <Florencia/Core/EntryPoint.h>
export module FloEditor;
import Florencia;

import EditorLayer;

namespace Florencia {

	class FloEditor final : public Application {
	public:
		FloEditor(std::string_view name, ApplicationCommandLineArgs args) : Application(name, args) {
			AddLayer(new EditorLayer());
		}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new FloEditor("FloEditor", args);
	}

}