#pragma once
#include <Florencia.h>

namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer(EventDispatcher& dispatcher);
		~EditorLayer() = default;

		void OnAdd() override;
		void OnRemove() override;

		void Update(Timestep ts) override;
		void OnEvent(Event& e) override;
		void Render() override;

		const char* GetName() const { return "EditorLayer"; }
	private:
		EventDispatcher& m_EventHandler;
	};

}