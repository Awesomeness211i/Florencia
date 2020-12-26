#include <Windows.h>
#include <Platform/Windows/Wwindow.h>
#include <Platform/Windows/WConsole.h>

namespace Florencia {

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_QUIT:
			return 0;
		case WM_DESTROY:
			PostQuitMessage((int)wParam);
			return 0;
		default:
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}
	}

	Wwindow::Wwindow(const WindowProps& props) {
		m_Data.Name = props.Name;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

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

		//Create Console
		#ifdef _DEBUG
		m_Console = new WConsole();
		m_Console->CreateNewConsole();
		#endif

		//Create Window
		RECT desktop = {0}, window = { 0, 0, m_Data.Width, m_Data.Height };
		HWND size = GetDesktopWindow();
		GetWindowRect(size, &desktop);

		AdjustWindowRect(&window, WS_OVERLAPPEDWINDOW, false);
		m_Handle = CreateWindowExA(
			NULL, "Window", &m_Data.Name[0],
			WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU|WS_VISIBLE,
			(desktop.right - m_Data.Width) / 2,
			(desktop.bottom - m_Data.Height) / 2,
			window.right - window.left, window.bottom - window.top,
			nullptr, nullptr, instance, 0);
	}

	Wwindow::~Wwindow() {
		//Destroy Console
		#ifdef _DEBUG
		m_Console->ReleaseConsole();
		delete m_Console;
		#endif
		HINSTANCE instance = GetModuleHandleA(0);
		UnregisterClassW(L"Window", instance);
	}

	bool Wwindow::OnUpdate() {
		MSG m_Message = { 0 };
		if (PeekMessageW(&m_Message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&m_Message);
			DispatchMessageA(&m_Message);
		}
		return m_Message.message != WM_QUIT;
	}

	void Wwindow::SetVSync(bool enabled) {
		m_Data.VSync = enabled;
	}

	bool Wwindow::IsVSync() const {
		return m_Data.VSync;
	}
}