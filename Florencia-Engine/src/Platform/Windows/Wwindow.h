#pragma once
#include <Windows.h>
#include <Core/Window.h>

namespace Florencia {
	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow() override;
		void OnUpdate() override;
	private:
		MSG m_Message;
		HWND m_Handle;
		WNDCLASSEX m_WClass;
	};
}