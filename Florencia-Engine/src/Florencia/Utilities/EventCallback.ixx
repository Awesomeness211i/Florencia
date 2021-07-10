export module EventCallback;
import Event;

namespace Florencia {

	export template<typename T>
	class EventCallback {
	public:
		EventCallback() = default;
		EventCallback(T* ptr, void(*f)(T*, Event&)) { ref = ptr; function = f; }
		void operator()(Event & e) { function(ref, e); }
	private:
		T* ref;
		void(*function)(T*, Event&);
	};

}