#pragma once

namespace Florencia {

	class Window {
	public:
		Window();
		virtual ~Window() = 0;

		virtual void SwapBuffers() = 0;

	private:

	};

}