export module LayerStack;
export import <vector>;
import <stdint.h>;
import Layer;

export namespace Florencia {

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

module: private;

namespace Florencia {

	LayerStack::~LayerStack() {
		for (auto layer : m_Layers) {
			layer->OnRemove();
			delete layer;
		}
	}

	void LayerStack::AddOverlay(Layer* layer) { m_Layers.emplace_back(layer); }
	void LayerStack::RemoveOverlay(Layer* layer) {
		//beginning of the overlay section is m_Layers.begin() + m_InsertIndex
		auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->OnRemove();
			m_Layers.erase(it);
		}
	}

	void LayerStack::AddLayer(Layer* layer) { m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer); m_InsertIndex++; }
	void LayerStack::RemoveLayer(Layer* layer) {
		//end of the normal layer vector is m_Layers.begin() + m_InsertIndex
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
		if (it != m_Layers.begin() + m_InsertIndex) {
			layer->OnRemove();
			m_Layers.erase(it);
			m_InsertIndex--;
		}
	}

	std::vector<Layer*>::iterator LayerStack::begin() { return m_Layers.begin(); }
	std::vector<Layer*>::reverse_iterator LayerStack::rbegin() { return m_Layers.rbegin(); }
	std::vector<Layer*>::const_iterator LayerStack::begin() const { return m_Layers.begin(); }
	std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const { return m_Layers.rbegin(); }

	std::vector<Layer*>::iterator LayerStack::end() { return m_Layers.end(); }
	std::vector<Layer*>::reverse_iterator LayerStack::rend() { return m_Layers.rend(); }
	std::vector<Layer*>::const_iterator LayerStack::end() const { return m_Layers.end(); }
	std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const { return m_Layers.rend(); }

}