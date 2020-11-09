#pragma once

namespace Florencia {

	class SwapChain {
	public:
		SwapChain() = default;
		virtual void Present() = 0;
	private:

	};

}