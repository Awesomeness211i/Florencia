#include "EditorLayer.h"

namespace Florencia {

	void EditorLayer::OnAttach() {
		
	}

	void EditorLayer::OnDetach() {

	}

	void EditorLayer::OnUpdate() {
		//Renderer::BeginScene();
		Renderer::EndScene();
	}

}