module;
#include <stdint.h>
struct HWND__; struct HINSTANCE__;
export module WindowsWindow;
import ApplicationEvent;
import KeyCodeConverter;
import MouseEvent;
import MouseCodes;
import KeyEvent;
import KeyCodes;
import Window;

export namespace Florencia {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props) : m_Data(props) { Init(props); }
		~WindowsWindow() { Shutdown(); }

		void Update() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		void SetWidth(uint32_t width) override { m_Data.Width = width; }
		void SetHeight(uint32_t height) override { m_Data.Height = height; }

		void* GetWindowHandle() override { return m_Handle; }

		long long WindowProcedure(HWND__* hWnd, unsigned int msg, unsigned long long wParam, long long lParam);
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		HWND__* m_Handle;
		WindowProps m_Data;
		HINSTANCE__* m_Instance;
	};
}