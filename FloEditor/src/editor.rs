use FlorenciaEngine::*;

pub struct EditorLayer {
}

impl Layer for EditorLayer {
	fn GetUUID(self: &Self) -> u64 {
		return 0;
	}
	
	fn OnAdd(self: &mut Self) {
		
	}

	fn OnRemove(self: &mut Self) {
		
	}

	fn OnEvent(self: &mut Self, e: &dyn Event) {
		
	}

	fn Update(self: &mut Self, ts: std::time::Duration) {

	}

	fn Render(self: &mut Self) {
		
	}
}

impl EditorLayer {
	pub fn new() -> Box<Self> {
		return Box::new(Self {
		});
	}
}
