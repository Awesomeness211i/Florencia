module;
#include <Windows.h>
export module Wwindow;
import Event.Application;
import Event.Mouse;
import Event.Key;
import Window;

export namespace Florencia {

	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props) : m_Data(props) { Init(props); }
		~Wwindow() { Shutdown(); }

		void OnUpdate() override {
			MSG m_Message = { 0 };
			if (PeekMessageW(&m_Message, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&m_Message);
				DispatchMessageA(&m_Message);
			}
		}

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		void SetWidth(uint32_t width) override { m_Data.Width = width; }
		void SetHeight(uint32_t height) override { m_Data.Height = height; }

		void* GetWindowHandle() override { return m_Handle; }

		static LONG_PTR WINAPI SetupWindowProcedure(HWND hWnd, UINT msg, UINT_PTR wParam, LONG_PTR lParam) {
			Wwindow* pParent;
			if (msg == WM_NCCREATE) {
				LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pParent = static_cast<Wwindow*>(lpcs->lpCreateParams);
				SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pParent));
			}
			else {
				pParent = reinterpret_cast<Wwindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
				if (!pParent) return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			if (pParent) return pParent->WindowProcedure(hWnd, msg, wParam, lParam);
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}

		LONG_PTR WINAPI WindowProcedure(HWND hWnd, UINT msg, UINT_PTR wParam, LONG_PTR lParam) {
			switch (msg) {
				case WM_QUIT: break;
				case WM_CHAR: break;
				case WM_KEYUP: { KeyReleasedEvent e(wParam); m_CallbackFunction(e); } break;
				case WM_KEYDOWN: { KeyPressedEvent e(wParam, 0); m_CallbackFunction(e); } break;
				case WM_DESTROY: { WindowCloseEvent e; m_CallbackFunction(e); } PostQuitMessage((int)wParam); break;
			}
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}
	private:
		void Init(const WindowProps& props) {
			HINSTANCE instance = GetModuleHandleA(0);
			WNDCLASSEXA wc = {0};
			wc.cbSize = sizeof(wc);
			wc.style = CS_OWNDC;
			wc.lpfnWndProc = SetupWindowProcedure;
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

			//Create Window
			RECT desktop = { 0 }, window = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height };
			HWND size = GetDesktopWindow();
			GetWindowRect(size, &desktop);
			AdjustWindowRect(&window, WS_OVERLAPPEDWINDOW, false);
			m_Handle = CreateWindowExA(
				NULL, "Window", m_Data.Title.c_str(),
				WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
				(desktop.right - m_Data.Width) / 2,
				(desktop.bottom - m_Data.Height) / 2,
				window.right - window.left, window.bottom - window.top,
				nullptr, nullptr, instance, this);
		}
		void Shutdown() {
			HINSTANCE instance = GetModuleHandleA(0);
			UnregisterClassW(L"Window", instance);
		}

		HWND m_Handle;
		WindowProps m_Data;
	};
}