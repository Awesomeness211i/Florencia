#pragma once
#include <FloMath.h>

namespace Florencia {

	class Console {
	public:
		virtual ~Console() = default;
		static Console* Create(int16 minLength = 1024);
	private:
		virtual bool CreateNewConsole() = 0;
		virtual bool ReleaseConsole() = 0;
	};

}