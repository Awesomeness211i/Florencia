#include <Florencia.h>

namespace Florencia {

	FLO_APPLICATION(FloEditor) {
	public:
		FloEditor(const ApplicationProps& props) : Application(props) {

		}

	};

	Application* CreateApplication() {
		ApplicationProps m_Data("FloEditor");
		return new FloEditor(m_Data);
	}
}
