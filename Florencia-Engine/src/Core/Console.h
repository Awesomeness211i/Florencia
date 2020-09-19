#pragma once
#include <stdint.h>

namespace Florencia {

	class Console {
	public:
		virtual ~Console() = default;
		virtual bool CreateNewConsole() = 0;
		virtual bool ReleaseConsole() = 0;
		static Console* Create(int16_t minLength = 1024);
	};

}