#pragma once
#include <Core/Window.h>

struct HWND__;
typedef HWND__* HWND;

namespace Florencia {
	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);

		void OnUpdate() override;
		void* GetWindowHandle() override { return m_Handle; }
	private:
		HWND m_Handle;
	};
}