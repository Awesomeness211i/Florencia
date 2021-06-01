#pragma once

namespace Florencia {

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;

		static GraphicsContext* Create(void* window, bool vsync = true);
	};

}