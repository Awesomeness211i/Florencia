#include "Wwindow.h"
#include <Windows.h>
#include <iostream>

namespace Florencia {

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	Wwindow::Wwindow(const WindowProps& props) {
		WNDCLASSEXA m_WClass;
		m_WClass.cbSize = sizeof(WNDCLASSEXA);
		m_WClass.cbClsExtra = 0;
		m_WClass.cbWndExtra = 0;
		m_WClass.hIconSm = nullptr;
		m_WClass.hInstance = NULL;
		m_WClass.lpfnWndProc = WndProc;
		m_WClass.style = CS_HREDRAW | CS_VREDRAW;
		m_WClass.lpszClassName = "C";
		m_WClass.lpszMenuName = "Menu";
		m_WClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_WClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_WClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		RegisterClassEx(&m_WClass);

		m_Handle = CreateWindowEx(WS_EX_ACCEPTFILES,"C",&props.name[0],WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,props.width,props.height,0,0,NULL,0);
		if (m_Handle == 0) {
			MessageBoxA(0, "Failed To Create Window", "Error", MB_ICONERROR | MB_ABORTRETRYIGNORE);
		}
	}

	void Wwindow::OnUpdate() {
		MSG m_Message;
		SecureZeroMemory(&m_Message, sizeof(MSG));
		GetMessage(&m_Message, 0, 0, 0);
		TranslateMessage(&m_Message);
		DispatchMessage(&m_Message);
	}

}