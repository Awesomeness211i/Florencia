export module Layer;
import TimeStep;
import Event;

export namespace Florencia {

	class Layer {
	public:
		Layer() {}
		virtual ~Layer() = default;

		virtual void OnAdd() = 0;
		virtual void OnRemove() = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void Render() = 0;
		virtual void Update(TimeStep ts) = 0;

		//For debug purposes only
		virtual const char* GetName() const = 0;
	};

}