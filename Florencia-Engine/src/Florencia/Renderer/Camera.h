#pragma once

namespace Florencia {

	class Camera {
	public:
		Camera() = default;
		//Camera(const glm::mat4& projection) : m_Projection(projection) {}
		virtual ~Camera() = default;
		//const FloMath::Mat4<float>& GetProjection() const { return m_Projection; }
	private:
		//FloMath::Mat4<float> m_Projection;
	};

	class OrthographicCamera : public Camera {
	public:

	private:

	};

	class PerspectiveCamera : public Camera {
	public:

	private:

	};

}