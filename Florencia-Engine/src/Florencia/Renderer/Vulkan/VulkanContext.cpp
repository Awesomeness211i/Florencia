module VulkanContext;
import GraphicsContext;

namespace Florencia {

	VulkanContext::VulkanContext(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

	void VulkanContext::Init() {

	}

	void VulkanContext::SwapBuffers() {

	}

	bool VulkanContext::IsVSync() const {
		return false;
	}

	void VulkanContext::SetVSync(bool enabled) {

	}

}