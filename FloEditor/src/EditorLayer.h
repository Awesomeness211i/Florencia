#pragma once
#include <Florencia.h>

namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		~EditorLayer() = default;

		void OnAdd() override;

		void Update(Timestep ts) override;
		void Render() override;

		void OnEvent(Event& e) override;

		void OnRemove() override;

		const char* GetName() const { return "EditorLayer"; }
	private:

	};

}