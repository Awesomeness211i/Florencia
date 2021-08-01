module;
#include <iostream>
export module EditorLayer;
import Florencia;

namespace Florencia {

	export class EditorLayer : public Layer {
	public:
		EditorLayer() = default;
		~EditorLayer() = default;

		void OnAdd() override;

		void OnRemove() override;

		void Update(TimeStep ts) override;

		void Render() override;

		void OnEvent(Event& e) override;

		bool OnCharacterTyped(CharacterTypedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnKeyReleased(KeyReleasedEvent& e);

		bool OnMousePressed(MouseButtonPressedEvent& e);

		bool OnMouseReleased(MouseButtonReleasedEvent& e);

		bool OnMouseMoved(MouseMovedEvent& e);

		bool OnMouseScrolled(MouseScrolledEvent& e);

		const char* GetName() const { return "EditorLayer"; }
	};

}

module: private;

namespace Florencia {

	void EditorLayer::OnAdd() {

	}

	void EditorLayer::OnRemove() {

	}

	void EditorLayer::Update(TimeStep ts) {
		
	}

	void EditorLayer::Render() {

	}

	void EditorLayer::OnEvent(Event& e) {
		EventHandler.Dispatch<KeyPressedEvent>(e, [this](KeyPressedEvent& e) -> bool { return EditorLayer::OnKeyPressed(e); });
		EventHandler.Dispatch<KeyReleasedEvent>(e, [this](KeyReleasedEvent& e) -> bool { return EditorLayer::OnKeyReleased(e); });
		EventHandler.Dispatch<CharacterTypedEvent>(e, [this](CharacterTypedEvent& e) -> bool { return EditorLayer::OnCharacterTyped(e); });

		EventHandler.Dispatch<MouseMovedEvent>(e, [this](MouseMovedEvent& e) -> bool { return EditorLayer::OnMouseMoved(e); });
		EventHandler.Dispatch<MouseScrolledEvent>(e, [this](MouseScrolledEvent& e) -> bool { return EditorLayer::OnMouseScrolled(e); });
		EventHandler.Dispatch<MouseButtonPressedEvent>(e, [this](MouseButtonPressedEvent& e) -> bool { return EditorLayer::OnMousePressed(e); });
		EventHandler.Dispatch<MouseButtonReleasedEvent>(e, [this](MouseButtonReleasedEvent& e) -> bool { return EditorLayer::OnMouseReleased(e); });
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