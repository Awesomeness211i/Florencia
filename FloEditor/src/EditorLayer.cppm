export module EditorLayer;
import <iostream>;
import Florencia;

export namespace Florencia {

	class EditorLayer : public Layer {
	public:
		EditorLayer(EventDispatcher& dispatcher) : m_EventHandler(dispatcher) {

		}

		~EditorLayer() = default;

		void OnAdd() override {

		}

		void OnRemove() override {

		}

		void Update(Timestep ts) override {
			
		}

		void OnEvent(Event& e) override {
			std::cout << e << "\n";
		}

		void Render() override {

		}

		const char* GetName() const { return "EditorLayer"; }
	private:
		EventDispatcher& m_EventHandler;
	};

}