module IPhoneWindow;

namespace Florencia {

	IPhoneWindow::IPhoneWindow(const WindowProps& props) {

	}

	IPhoneWindow::~IPhoneWindow() {

	}

	void IPhoneWindow::OnUpdate() {

	}

	uint32_t IPhoneWindow::GetWidth() const {
		return 0;
	}

	uint32_t IPhoneWindow::GetHeight() const {
		return 0;
	}

	bool IPhoneWindow::IsVSync() const {
		return false;
	}

	void IPhoneWindow::SetVSync(bool enabled) {

	}

	void IPhoneWindow::SetWidth(uint32_t width) {

	}

	void IPhoneWindow::SetHeight(uint32_t height) {

	}

	void* IPhoneWindow::GetWindowHandle() {
		return nullptr;
	}

}