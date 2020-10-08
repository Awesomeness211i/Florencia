#pragma once
#include <functional>
#include <Core/Console.h>
#include <Events/AppEvent.h>

namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, unsigned width, unsigned height)
			: Name(title), Width(width), Height(height) {}
		std::string Name;
		unsigned Width, Height;
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window();
		virtual ~Window();

		virtual void OnUpdate() = 0;

		virtual Uint32 GetWidth() const = 0;
		virtual Uint32 GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	private:
	#ifdef _DEBUG
		Console* m_Console;
	#endif
	};
}