import MetalContext;

namespace Florencia {

	MetalContext::MetalContext(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

	void MetalContext::Init() {

	}

	void MetalContext::SwapBuffers() {

	}

	bool MetalContext::IsVSync() const {
		return false;
	}

	void MetalContext::SetVSync(bool enabled) {

	}

}