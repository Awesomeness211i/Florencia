module;
#include <vector>
export module Renderer;
import RenderContext;

namespace Florencia {

	export class Renderer {
	public:
		Renderer(RenderContext& context);

	private:
		RenderContext& m_Contexts;
	};

}

module: private;

namespace Florencia {

	Renderer::Renderer(RenderContext& context) : m_Contexts(context) {}

}