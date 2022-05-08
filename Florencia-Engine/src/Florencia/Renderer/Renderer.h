#pragma once
#include <vector>
#include "RenderContext.h"

namespace Florencia {

	class Renderer {
	public:
		Renderer(RenderContext& context);

	private:
		RenderContext& m_Contexts;
	};

}
