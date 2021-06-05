#include "DirectX12Context.h"

namespace Florencia {

    DirectX12Context::DirectX12Context(void* window, bool vsync) : m_WindowHandle(window), m_Vsync(vsync) {}

    void DirectX12Context::Init() {

    }

    void DirectX12Context::SwapBuffers() {

    }

    bool DirectX12Context::IsVSync() const {
        return false;
    }

    void DirectX12Context::SetVSync(bool enabled) {

    }

}