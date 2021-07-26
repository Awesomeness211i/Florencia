/*module;
#define _GLFW_WIN32
#include "../../Florencia-Engine/vendor/glfw/src/internal.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
export module Test;
import Window;

namespace Florencia {

	template <typename T>
	GLFWwindow* glfwAttachWin32Window(const Window<T>& handle, GLFWwindow* share) {
		_GLFWfbconfig fbconfig;
		_GLFWctxconfig ctxconfig;
		_GLFWwndconfig wndconfig;
		_GLFWwindow* window;

		_GLFW_REQUIRE_INIT_OR_RETURN(NULL);

		fbconfig = _glfw.hints.framebuffer;
		ctxconfig = _glfw.hints.context;
		wndconfig = _glfw.hints.window;

		ctxconfig.share = (_GLFWwindow*)share;
		if (ctxconfig.share) {
			if (ctxconfig.client == GLFW_NO_API || ctxconfig.share->context.client == GLFW_NO_API) {
				_glfwInputError(GLFW_NO_WINDOW_CONTEXT, NULL);
				return NULL;
			}
		}

		if (!_glfwIsValidContextConfig(&ctxconfig)) return NULL;

		window = calloc(1, sizeof(_GLFWwindow));
		window->next = _glfw.windowListHead;
		_glfw.windowListHead = window;

		window->autoIconify = wndconfig.autoIconify;
		window->cursorMode = GLFW_CURSOR_NORMAL;

		window->minwidth = GLFW_DONT_CARE;
		window->minheight = GLFW_DONT_CARE;
		window->maxwidth = GLFW_DONT_CARE;
		window->maxheight = GLFW_DONT_CARE;
		window->numer = GLFW_DONT_CARE;
		window->denom = GLFW_DONT_CARE;

		window->win32.handle = (HWND)handle.GetWindowHandle();

		//SetPropW(window->win32.handle, L"GLFW", window);
		//SetWindowLongPtrW(window->win32.handle, GWLP_WNDPROC, (LONG_PTR)windowProc);

		{
			const DWORD style = GetWindowLongW(window->win32.handle, GWL_STYLE);
			const DWORD exStyle = GetWindowLongW(window->win32.handle, GWL_EXSTYLE);
			if (style & WS_THICKFRAME) window->resizable = GLFW_TRUE;
			if (style & (WS_BORDER | WS_THICKFRAME)) window->decorated = GLFW_TRUE;
			if (exStyle & WS_EX_TOPMOST) window->floating = GLFW_TRUE;
			window->win32.maximized = IsZoomed(window->win32.handle);
			window->win32.iconified = IsIconic(window->win32.handle);
		}

		if (ctxconfig.client != GLFW_NO_API) {
			if (ctxconfig.source == GLFW_NATIVE_CONTEXT_API) {
				if (!_glfwInitWGL()) return GLFW_FALSE;
				if (!_glfwCreateContextWGL(window, &ctxconfig, &fbconfig)) return GLFW_FALSE;
			}
			else if (ctxconfig.source == GLFW_EGL_CONTEXT_API) {
				if (!_glfwInitEGL()) return GLFW_FALSE;
				if (!_glfwCreateContextEGL(window, &ctxconfig, &fbconfig)) return GLFW_FALSE;
			}
			else if (ctxconfig.source == GLFW_OSMESA_CONTEXT_API) {
				if (!_glfwInitOSMesa()) return GLFW_FALSE;
				if (!_glfwCreateContextOSMesa(window, &ctxconfig, &fbconfig)) return GLFW_FALSE;
			}
		}

		if (ctxconfig.client != GLFW_NO_API) {
			if (!_glfwRefreshContextAttribs(window, &ctxconfig)) {
				glfwDestroyWindow((GLFWwindow*)window);
				return NULL;
			}
		}

		return (GLFWwindow*)window;
	}

}*/