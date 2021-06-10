module EditorLayer;
import Florencia;

namespace Florencia {

	EditorLayer::EditorLayer(EventDispatcher& dispatcher) : m_EventHandler(dispatcher) {

	}

	void EditorLayer::OnAdd() {

	}

	void EditorLayer::OnRemove() {

	}

	void EditorLayer::Update(Timestep ts) {

	}

	void EditorLayer::OnEvent(Event& e) {
		//m_EventHandler.Dispatch<KeyPressedEvent>(e, [this](WindowCloseEvent& e) -> bool { return this->EditorLayer::Test(e); });
	}

	void EditorLayer::Render() {

	}

}