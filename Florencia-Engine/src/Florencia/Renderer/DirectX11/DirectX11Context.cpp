module DirectX11Context;

namespace Florencia {

	DirectX11Context::DirectX11Context(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

	void DirectX11Context::Init() {

	}

	void DirectX11Context::SwapBuffers() {

	}

	bool DirectX11Context::IsVSync() const {
		return false;
	}

	void DirectX11Context::SetVSync(bool enabled) {

	}

}