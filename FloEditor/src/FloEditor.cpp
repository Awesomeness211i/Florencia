#include "EditorLayer.h"
#include <Florencia/Core/EntryPoint.h>

namespace Florencia {

	FLO_APPLICATION(FloEditor) {
	public:
		FloEditor(const WindowProps& props) : Application(props) {
			AddLayer(new EditorLayer());
		}

	};

	Application* CreateApplication() {
		WindowProps m_Data("FloEditor", 1080, 720);
		return new FloEditor(m_Data);
	}
}
