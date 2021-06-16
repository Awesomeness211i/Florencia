export module Wwindow;
import Event.Application;
import GraphicsContext;
import <Windows.h>;
import WConsole;
import Window;

export namespace Florencia {

	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
		void SetWidth(uint32_t width) override;
		void SetHeight(uint32_t height) override;

		void* GetWindowHandle() override { return m_Handle; }

		static LONG_PTR WINAPI SetupWindowProcedure(HWND hWnd, UINT msg, UINT_PTR wParam, LONG_PTR lParam);
		LONG_PTR WINAPI WindowProcedure(HWND hWnd, UINT msg, UINT_PTR wParam, LONG_PTR lParam);
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		HWND m_Handle;
		WindowProps m_Data;
		GraphicsContext* m_Context;

		#if defined(FLO_DEBUG) || defined(FLO_RELEASE)
		WConsole* m_Console;
		#endif
	};
}