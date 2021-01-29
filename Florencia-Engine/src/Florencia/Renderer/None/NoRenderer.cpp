#include "NoRenderer.h"

namespace Florencia {

	NoRenderer::NoRenderer(API api) : Renderer(api) {

	}

	void NoRenderer::Init(void* window) {

	}

	void NoRenderer::Clear() {
		return;
	}

	void NoRenderer::SetClearColor(float r, float g, float b, float a) {
		return;
	}

}