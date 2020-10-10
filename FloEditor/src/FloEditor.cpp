#include <Florencia.h>

namespace Florencia {

	class FloEditor : public Application {
	public:
		FloEditor()
			:Application("Flo Editor")
		{

		}

		~FloEditor() {

		}
	};

	FLO_CREATE_APP(FloEditor)
}