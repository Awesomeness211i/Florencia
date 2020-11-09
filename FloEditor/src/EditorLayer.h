#pragma once
#include <Florencia.h>

namespace Florencia {

	class EditorLayer : public Layer {
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:

	};

}