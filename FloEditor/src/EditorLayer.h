#pragma once
#include <Florencia.h>

namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		~EditorLayer();

		void OnAdd() override;
		void OnEvent(Event& e) override;
		void OnRemove() override;

		void Render() override;
		void Update(Timestep ts) override;
	private:

	};

}