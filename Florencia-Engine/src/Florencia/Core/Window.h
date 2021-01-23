#pragma once
#include <functional>
#include <Math/FloMath.h>
#include <Renderer/Renderer.h>

namespace Florencia {

	struct WindowProps {
		WindowProps(const std::string& title, unsigned width, unsigned height)
			: Name(title), Width(width), Height(height) {}
		std::string Name;
		unsigned Width, Height;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual bool OnUpdate() = 0;

		virtual Uint32 GetWidth() const = 0;
		virtual Uint32 GetHeight() const = 0;

		//Window Attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	};
}