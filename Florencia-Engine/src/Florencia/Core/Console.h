#pragma once

namespace Florencia {

	class Console {
	public:
		Console() = default;
		virtual ~Console() = default;

		virtual bool AllocateConsole() = 0;
		virtual bool ReleaseConsole() = 0;
	};

}