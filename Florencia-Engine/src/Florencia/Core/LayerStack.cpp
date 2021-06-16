module LayerStack;

namespace Florencia {

	LayerStack::~LayerStack() {

		for (auto layer : m_Layers) {
			layer->OnRemove();
			delete layer;
		}

	}

	//Overlays go to end of vector
	void LayerStack::AddOverlay(Layer* layer) {
		//adds overlay to the end of list
		m_Layers.emplace_back(layer);
	}

	void LayerStack::RemoveOverlay(Layer* layer) {
		//beginning of the overlay section is m_Layers.begin() + m_InsertIndex
		auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->OnRemove();
			m_Layers.erase(it);
		}
	}

	void LayerStack::AddLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
	}

	void LayerStack::RemoveLayer(Layer* layer) {
		//end of the normal layer vector is m_Layers.begin() + m_InsertIndex
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
		if (it != m_Layers.begin() + m_InsertIndex) {
			layer->OnRemove();
			m_Layers.erase(it);
			m_InsertIndex--;
		}
	}

}