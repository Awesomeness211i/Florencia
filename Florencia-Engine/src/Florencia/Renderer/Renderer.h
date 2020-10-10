#pragma once
#include <FloMath.h>

namespace Florencia {

	struct RenderData {
		
	};

	class Renderer {
	public:
		static void Init();
		static void Draw();
		static void Submit(const RenderData& data);
	private:
		static Renderer* m_Instance;
	};

}