module EditorLayer;

namespace Florencia {

	void EditorLayer::OnAdd() {
		
	}

	void EditorLayer::OnRemove() {
		
	}

	void EditorLayer::Update(Timestep ts) {

	}

	void EditorLayer::Render() {

	}

	void EditorLayer::OnEvent(Event& e) {
		EventHandler.Dispatch<KeyPressedEvent>(e, [this](KeyPressedEvent& e) -> bool { return this->EditorLayer::OnKeyPressed(e); });
		EventHandler.Dispatch<KeyReleasedEvent>(e, [this](KeyReleasedEvent& e) -> bool { return this->EditorLayer::OnKeyReleased(e); });
		EventHandler.Dispatch<CharacterTypedEvent>(e, [this](CharacterTypedEvent& e) -> bool { return this->EditorLayer::OnCharacterTyped(e); });
		
		EventHandler.Dispatch<MouseMovedEvent>(e, [this](MouseMovedEvent& e) -> bool { return this->EditorLayer::OnMouseMoved(e); });
		EventHandler.Dispatch<MouseScrolledEvent>(e, [this](MouseScrolledEvent& e) -> bool { return this->EditorLayer::OnMouseScrolled(e); });
		EventHandler.Dispatch<MouseButtonPressedEvent>(e, [this](MouseButtonPressedEvent& e) -> bool { return this->EditorLayer::OnMousePressed(e); });
		EventHandler.Dispatch<MouseButtonReleasedEvent>(e, [this](MouseButtonReleasedEvent& e) -> bool { return this->EditorLayer::OnMouseReleased(e); });
	}

	bool EditorLayer::OnCharacterTyped(CharacterTypedEvent& e) {
		return true;
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		return true;
	}

	bool EditorLayer::OnKeyReleased(KeyReleasedEvent& e) {
		return true;
	}

	bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e) {
		return true;
	}

	bool EditorLayer::OnMouseReleased(MouseButtonReleasedEvent& e) {
		return true;
	}

	bool EditorLayer::OnMouseMoved(MouseMovedEvent& e) {
		return true;
	}

	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& e) {
		return true;
	}

}