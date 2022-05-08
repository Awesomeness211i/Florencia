#pragma once
#include <vector>
#include "RenderContext.h"

namespace Florencia {

	export class Renderer {
	public:
		Renderer(RenderContext& context);

	private:
		RenderContext& m_Contexts;
	};

}

namespace Florencia {

	Renderer::Renderer(RenderContext& context) : m_Contexts(context) {}

}