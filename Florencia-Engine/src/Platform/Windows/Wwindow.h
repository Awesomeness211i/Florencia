#pragma once
#include <Core/Window.h>
#include <Platform/Windows/WConsole.h>

struct HWND__; typedef HWND__* HWND;

namespace Florencia {

	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow();

		void OnRender() override;
		bool OnUpdate() override;

		Uint32 GetWidth() const override { return m_Data.Width; }
		Uint32 GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
		void SetWidth(Uint32 width) override;
		void SetHeight(Uint32 height) override;

		void* GetWindowHandle() override { return m_Handle; }
	private:
		Renderer* renderer;
		WindowProps m_Data;
		HWND m_Handle;

		#ifdef _DEBUG
		WConsole* m_Console;
		#endif
	};
}