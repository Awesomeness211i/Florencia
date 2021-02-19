#pragma once
#include <functional>
#include "../Math/FloMath.h"
#include "../Renderer/Renderer.h"

namespace Florencia {

	struct WindowProps {
		bool VSync = true;
		std::string Name = "";
		unsigned Width = 0, Height = 0;
		Renderer::API API = Renderer::API::None;
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void OnRender() = 0;
		virtual bool OnUpdate() = 0;

		virtual Uint32 GetWidth() const = 0;
		virtual Uint32 GetHeight() const = 0;

		//Window Attributes
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetWidth(Uint32 width) = 0;
		virtual void SetHeight(Uint32 height) = 0;

		virtual void* GetWindowHandle() = 0;

		static Window* Create(const WindowProps& props);
	};
}
