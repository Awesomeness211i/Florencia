#pragma once
#include <GLFW/glfw3.h>
#include "Florencia/Core/Window.h"

namespace Florencia {

	class RenderContext {
	public:
		RenderContext(Window& window);
		~RenderContext();

		void Init(Window& window);

		void SwapBuffers();
	private:
		GLFWwindow* m_Window = nullptr;
	};

}
