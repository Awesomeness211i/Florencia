#pragma once
#include <Core/Window.h>

struct HWND__;
typedef HWND__* HWND;

namespace Florencia {
	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow() override;

		void OnUpdate() override;

		Uint32 GetWidth() const override { return m_Data.Width; }
		Uint32 GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetWindowHandle() override { return m_Handle; }
	private:
		struct WindowData {
			std::string Name = "";
			unsigned Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
		HWND m_Handle;
	};
}