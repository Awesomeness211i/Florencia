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
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
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
		wc.hIcon = nullptr; /*LoadIcon(instance, IDI_APPLICATION);*/
		wc.hCursor = nullptr;/*LoadCursor(instance, IDC_ARROW);*/
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = "Window";
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);

		m_Handle = CreateWindowEx(0,"Window",&props.name[0],WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU|WS_VISIBLE,0,0,props.width,props.height,0,0,instance,0);
	}

	void Wwindow::OnUpdate() {
		MSG m_Message;
		SecureZeroMemory(&m_Message, sizeof(MSG));
		GetMessage(&m_Message, 0, 0, 0);
		TranslateMessage(&m_Message);
		DispatchMessage(&m_Message);
	}

}