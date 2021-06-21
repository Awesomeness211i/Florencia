module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module WindowsWindow;
import Event.Application;
import KeyCodeConverter;
import Event.Mouse;
import MouseCodes;
import Event.Key;
import KeyCodes;
import Window;

export namespace Florencia {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props) : m_Data(props) { Init(props); }
		~WindowsWindow() { Shutdown(); }

		void OnUpdate() override {
			MSG m_Message = {0};
			if (PeekMessageW(&m_Message, 0, 0, 0, PM_REMOVE)) [[likely]] {
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
			WindowsWindow* pParent;
			if (msg != WM_NCCREATE) [[likely]] {
				pParent = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
				if (!pParent) return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			else [[unlikely]] {
				LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pParent = static_cast<WindowsWindow*>(lpcs->lpCreateParams);
				SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pParent));
			}
			return pParent->WindowProcedure(hWnd, msg, wParam, lParam);
		}

		LONG_PTR WINAPI WindowProcedure(HWND hWnd, UINT msg, UINT_PTR wParam, LONG_PTR lParam) {
			switch (msg) {
				case WM_CLOSE: { WindowCloseEvent e; m_CallbackFunction(e); } return 0;

				case WM_KEYDOWN: { KeyPressedEvent e(ConvertToUniversalKeyCode(wParam), 0); m_CallbackFunction(e); } return 0;
				case WM_KEYUP: { KeyReleasedEvent e(ConvertToUniversalKeyCode(wParam)); m_CallbackFunction(e); } return 0;
				case WM_CHAR: { CharacterTypedEvent e((Character)wParam); m_CallbackFunction(e); } return 0;

				case WM_LBUTTONDOWN: { MouseButtonPressedEvent e(MouseButton::Left); m_CallbackFunction(e); } return 0;
				case WM_RBUTTONDOWN: { MouseButtonPressedEvent e(MouseButton::Right); m_CallbackFunction(e); } return 0;
				case WM_MBUTTONDOWN: { MouseButtonPressedEvent e(MouseButton::Middle); m_CallbackFunction(e); } return 0;

				case WM_LBUTTONUP: { MouseButtonReleasedEvent e(MouseButton::Left); m_CallbackFunction(e); } return 0;
				case WM_RBUTTONUP: { MouseButtonReleasedEvent e(MouseButton::Right); m_CallbackFunction(e); } return 0;
				case WM_MBUTTONUP: { MouseButtonReleasedEvent e(MouseButton::Middle); m_CallbackFunction(e); } return 0;

				case WM_MOUSEMOVE: { POINTS p = MAKEPOINTS(lParam); MouseMovedEvent e((int)p.x, (int)p.y); m_CallbackFunction(e); } return 0;
				case WM_MOUSEWHEEL: { short p = GET_WHEEL_DELTA_WPARAM(wParam); MouseScrolledEvent e((int)p, 0); m_CallbackFunction(e); } return 0;
			}
			return DefWindowProcA(hWnd, msg, wParam, lParam);
		}
	private:
		void Init(const WindowProps& props) {
			m_Instance = GetModuleHandleA(0);
			m_WindowsClass.cbSize = sizeof(m_WindowsClass);
			m_WindowsClass.style = CS_OWNDC;
			m_WindowsClass.lpfnWndProc = SetupWindowProcedure;
			m_WindowsClass.cbClsExtra = 0;
			m_WindowsClass.cbWndExtra = 0;
			m_WindowsClass.hInstance = m_Instance;
			m_WindowsClass.hIcon = static_cast<HICON>(LoadImage(m_Instance, MAKEINTRESOURCE(101), IMAGE_ICON, 256, 256, 0));
			m_WindowsClass.hCursor = nullptr;
			m_WindowsClass.hbrBackground = nullptr;
			m_WindowsClass.lpszMenuName = nullptr;
			m_WindowsClass.lpszClassName = "Window";
			m_WindowsClass.hIconSm = static_cast<HICON>(LoadImage(m_Instance, MAKEINTRESOURCE(101), IMAGE_ICON, 16, 16, 0));
			RegisterClassExA(&m_WindowsClass);

			//Create Window
			RECT desktop = {0}, window = { 0, 0, (LONG)m_Data.Width, (LONG)m_Data.Height };
			HWND size = GetDesktopWindow();
			GetWindowRect(size, &desktop);
			AdjustWindowRect(&window, WS_OVERLAPPEDWINDOW, false);
			m_Handle = CreateWindowExA(
				NULL, "Window", m_Data.Title.c_str(),
				WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
				(desktop.right - m_Data.Width) / 2,
				(desktop.bottom - m_Data.Height) / 2,
				window.right - window.left, window.bottom - window.top,
				nullptr, nullptr, m_Instance, this);
		}

		void Shutdown() {
			DestroyWindow(m_Handle);
			UnregisterClassW(L"Window", m_Instance);
		}

		HWND m_Handle;
		WindowProps m_Data;
		HINSTANCE m_Instance;
		WNDCLASSEXA m_WindowsClass = {0};
	};
}