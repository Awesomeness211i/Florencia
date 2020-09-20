#pragma once
#include <Core/Window.h>

namespace Florencia {
	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);

		void OnUpdate() override;
		void* GetWindowHandle() override { return m_Handle; }
	};
}