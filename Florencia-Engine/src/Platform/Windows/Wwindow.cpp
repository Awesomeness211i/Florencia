#include "Wwindow.h"
#include <Windows.h>

namespace Florencia {

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage((int)wParam);
			return 0;
		default:
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}
	}

	Wwindow::Wwindow(const WindowProps& props) {
		HINSTANCE instance = GetModuleHandleA(0);
		WNDCLASSEXA wc = {0};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = instance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = "Window";
		wc.hIconSm = nullptr;
		RegisterClassExA(&wc);

		RECT desktop = {0};
		HWND size = GetDesktopWindow();
		GetWindowRect(size, &desktop);

		m_Data.Name = props.Name;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		m_Handle = CreateWindowExA(
			NULL, "Window", &m_Data.Name[0],
			WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU|WS_VISIBLE,
			(desktop.right - m_Data.Width) / 2,
			(desktop.bottom - m_Data.Height) / 2,
			m_Data.Width, m_Data.Height,
			nullptr, nullptr, instance, 0);
	}

	Wwindow::~Wwindow() {
		HINSTANCE instance = GetModuleHandleA(0);
		UnregisterClass("Window", instance);
	}

	void Wwindow::OnUpdate() {
		MSG m_Message = {0};
		GetMessageA(&m_Message, 0, 0, 0);
		TranslateMessage(&m_Message);
		DispatchMessageA(&m_Message);
		
		//Test of Cherno's event system
		AppUpdateEvent event;
		m_Data.EventCallback(event);
	}

	void Wwindow::SetVSync(bool enabled) {
	}

	bool Wwindow::IsVSync() const {
		return false;
	}
}