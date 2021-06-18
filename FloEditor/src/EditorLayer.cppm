export module EditorLayer;
import Florencia;

export namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer() {

		}

		~EditorLayer() = default;

		void OnAdd() override {

		}

		void OnRemove() override {

		}

		void Update(Timestep ts) override {
			
		}

		void OnEvent(Event& e) override {
			EventHandler.Dispatch<KeyPressedEvent>(e, [this](KeyPressedEvent& e) -> bool { return this->EditorLayer::OnKeyPressed(e); });
			EventHandler.Dispatch<KeyReleasedEvent>(e, [this](KeyReleasedEvent& e) -> bool { return this->EditorLayer::OnKeyReleased(e); });
			EventHandler.Dispatch<MouseButtonPressedEvent>(e, [this](MouseButtonPressedEvent& e) -> bool { return this->EditorLayer::OnMousePressed(e); });
			EventHandler.Dispatch<MouseButtonReleasedEvent>(e, [this](MouseButtonReleasedEvent& e) -> bool { return this->EditorLayer::OnMouseReleased(e); });
		}

		bool OnKeyPressed(KeyPressedEvent& e) {
			return true;
		}

		bool OnKeyReleased(KeyReleasedEvent& e) {
			return true;
		}

		bool OnMousePressed(MouseButtonPressedEvent& e) {
			return true;
		}

		bool OnMouseReleased(MouseButtonReleasedEvent& e) {
			return true;
		}

		const char* GetName() const { return "EditorLayer"; }
	};

}