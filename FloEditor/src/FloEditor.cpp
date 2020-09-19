#include "Florencia.h"

namespace Florencia {

	class FloEditor : public Application {
	public:
		FloEditor()
			:Application("Flo Editor")
		{}

		~FloEditor() {}
	};

	Application* CreateApplication() {
		return new FloEditor();
	}

}