#include "Florencia.h"

namespace Florencia {

	class EditorLayer : public Layer {
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