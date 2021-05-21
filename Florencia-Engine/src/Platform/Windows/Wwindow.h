#pragma once
#include <Florencia/Core/Window.h>
#include <Florencia/Renderer/GraphicsContext.h>
#include "WConsole.h"

struct HWND__;

namespace Florencia {

	class Wwindow : public Window {
	public:
		Wwindow(const WindowProps& props);
		~Wwindow();

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
		void Init(const WindowProps& props);
		void Shutdown();

		HWND__* m_Handle;
		WindowProps m_Data;
		GraphicsContext* m_Context;

		#ifdef _DEBUG
		WConsole* m_Console;
		#endif
	};
}
