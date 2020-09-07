#include "FloEditor.h"
#include <iostream>

namespace Florencia {

	FloEditor::FloEditor() {
		std::cout << "Constructed!";
	}

	FloEditor::~FloEditor() {

	}

	Application* CreateApplication() {
		return new FloEditor();
	}
	
}