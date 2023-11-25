use FlorenciaEngine::*;

pub struct EditorLayer {
}

impl Layer for EditorLayer {
	fn GetUUID(&self) -> u64 {
		0
	}
	
	fn OnAdd(&mut self) {
		
	}

	fn OnRemove(&mut self) {
		
	}

	fn OnEvent(&mut self, e: &dyn Event) {
		
	}

	fn Update(&mut self, ts: std::time::Duration) {

	}

	fn Render(&mut self) {
		
	}
}

impl EditorLayer {
	pub fn new() -> Box<Self> {
		Box::new(Self {
		})
	}
}
