#pragma once
#include <Core/Window.h>

struct HWND__; typedef HWND__* HWND;

namespace Florencia {
	#if defined(_DEBUG)
	class WConsole;
	#endif

	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow();

		bool OnUpdate() override;

		Uint32 GetWidth() const override { return m_Data.Width; }
		Uint32 GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetWindowHandle() override { return m_Handle; }
	private:
		struct WindowData {
			std::string Name = "";
			unsigned Width = 0, Height = 0;
			bool VSync = true;
		};
		Renderer* renderer;
		WindowData m_Data;
		HWND m_Handle;

		#ifdef _DEBUG
		WConsole* m_Console;
		#endif
	};
}