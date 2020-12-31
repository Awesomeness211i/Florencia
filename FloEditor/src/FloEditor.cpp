#include <Florencia.h>
#include <Florencia/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Florencia {

	FLO_APPLICATION(FloEditor) {
	public:
		FLO_APP_CONSTRUCTOR(FloEditor, "Florencia Editor") {
			PushLayer(new EditorLayer);
		}

		~FloEditor() {}
	};

	FLO_CREATE_APP(FloEditor)
}