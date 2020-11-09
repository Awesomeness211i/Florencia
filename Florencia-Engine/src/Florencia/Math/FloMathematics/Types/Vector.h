#pragma once

namespace FloMath {

	template<typename T, unsigned Dim>
	class Vector {
	public:

	private:
		T data[Dim];
	};

	typedef Vector<int, 2> Vec2i;
	typedef Vector<int, 3> Vec3i;
	typedef Vector<int, 4> Vec4i;

	typedef Vector<unsigned, 2> Vec2Ui;
	typedef Vector<unsigned, 3> Vec3Ui;
	typedef Vector<unsigned, 4> Vec4Ui;

	typedef Vector<float, 2> Vec2f;
	typedef Vector<float, 3> Vec3f;
	typedef Vector<float, 4> Vec4f;

}