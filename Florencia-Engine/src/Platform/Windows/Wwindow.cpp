#include "Wwindow.h"
#include <Windows.h>
#include <iostream>

namespace Florencia {

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(wParam);
			return 0;
		default:
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}
	}

	Wwindow::Wwindow(const WindowProps& props) {
		HINSTANCE instance = GetModuleHandle(0);
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

		m_Handle = CreateWindowExA(
			NULL, "Window", &props.m_Name[0],
			WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU|WS_VISIBLE,
			(desktop.right - props.m_Width) / 2,
			(desktop.bottom - props.m_Height) / 2,
			props.m_Width, props.m_Height,
			nullptr, nullptr, instance, 0);
	}

	void Wwindow::OnUpdate() {
		MSG m_Message = {0};
		GetMessageA(&m_Message, 0, 0, 0);
		TranslateMessage(&m_Message);
		DispatchMessageA(&m_Message);
	}

}