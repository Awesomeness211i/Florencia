module;
export module EditorLayer;
import Florencia;

export namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer() = default;
		~EditorLayer() = default;

		void OnAdd() override;

		void OnRemove() override;

		void Update(Timestep ts) override;

		void Render() override;

		bool OpenConsole() {
			m_Console = Console::Create();
			if (m_Console) [[likely]] {
				m_Console->CreateNewConsole();
			}
			return true;
		}

		bool CloseConsole() {
			if (m_Console) [[likely]] {
				m_Console->ReleaseConsole();
				delete m_Console;
				m_Console = nullptr;
			}
			return true;
		}

		void OnEvent(Event& e) override;

		bool OnCharacterTyped(CharacterTypedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnKeyReleased(KeyReleasedEvent& e);

		bool OnMousePressed(MouseButtonPressedEvent& e);

		bool OnMouseReleased(MouseButtonReleasedEvent& e);

		bool OnMouseMoved(MouseMovedEvent& e);

		bool OnMouseScrolled(MouseScrolledEvent& e);

		const char* GetName() const { return "EditorLayer"; }

	private:
		Console* m_Console;
	};

}