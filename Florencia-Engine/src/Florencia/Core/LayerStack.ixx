module;
#include <vector>
#include <stdint.h>
export module LayerStack;
import Layer;

export namespace Florencia {

	class LayerStack {
	public:
		LayerStack() = default;

		~LayerStack() {
			for (auto layer : m_Layers) {
				layer->OnRemove();
				delete layer;
			}
		}

		//Overlays go to end of vector
		void AddOverlay(Layer* layer) {
			m_Layers.emplace_back(layer);
		}

		void RemoveOverlay(Layer* layer) {
			//beginning of the overlay section is m_Layers.begin() + m_InsertIndex
			auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), layer);
			if (it != m_Layers.end()) {
				layer->OnRemove();
				m_Layers.erase(it);
			}
		}

		void AddLayer(Layer* layer) {
			m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
			m_InsertIndex++;
		}

		void RemoveLayer(Layer* layer) {
			//end of the normal layer vector is m_Layers.begin() + m_InsertIndex
			auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
			if (it != m_Layers.begin() + m_InsertIndex) {
				layer->OnRemove();
				m_Layers.erase(it);
				m_InsertIndex--;
			}
		}

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }

		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_InsertIndex = 0;
	};

}