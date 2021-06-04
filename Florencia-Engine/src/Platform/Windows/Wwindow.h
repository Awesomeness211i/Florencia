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

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		//Window Attributes
		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
		void SetWidth(uint32_t width) override;
		void SetHeight(uint32_t height) override;

		void* GetWindowHandle() override { return m_Handle; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		HWND__* m_Handle;
		WindowProps m_Data;
		GraphicsContext* m_Context;

		#ifdef FLO_DEBUG
		WConsole* m_Console;
		#endif
	};
}
