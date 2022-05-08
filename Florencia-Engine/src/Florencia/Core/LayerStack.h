#pragma once
#include <vector>
#include <stdint.h>
#include "Layer.h"

namespace Florencia {

	class LayerStack final {
	public:
		LayerStack() = default;
		~LayerStack();

		//Overlays go to end of vector
		void AddOverlay(Layer* layer);
		void RemoveOverlay(Layer* layer);

		void AddLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::reverse_iterator rbegin();
		std::vector<Layer*>::const_iterator begin() const;
		std::vector<Layer*>::const_reverse_iterator rbegin() const;

		std::vector<Layer*>::iterator end();
		std::vector<Layer*>::reverse_iterator rend();
		std::vector<Layer*>::const_iterator end() const;
		std::vector<Layer*>::const_reverse_iterator rend() const;

	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_InsertIndex = 0;
	};

}