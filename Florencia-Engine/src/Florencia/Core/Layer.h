#pragma once
#include <Florencia/Events/Event.h>
#include <Florencia/Core/Timestep.h>

namespace Florencia {

	class Layer {
	public:
		Layer() {}
		virtual ~Layer() = default;

		virtual void OnAdd() = 0;
		virtual void OnRemove() = 0;
		virtual void OnEvent(Event& e) {}
		
		virtual void Render() {}
		virtual void Update(Timestep ts) = 0;
	};

}