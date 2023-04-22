use FlorenciaEngine::*;

pub struct EditorLayer {
	uuid: u64,
}

impl Layer for EditorLayer {
	fn OnAdd(self: &Self) {
		
	}
	fn OnRemove(self: &Self) {
		
	}
	fn OnEvent(self: &Self, e: &dyn Event) {
		
	}
	fn Update(self: &Self, ts: f64) {

	}
	fn Render(self: &Self) {
		
	}
	fn GetUUID(self: &Self) -> u64 {
		self.uuid
	}
}

impl EditorLayer {
	pub fn new() -> Box<Self> {
        return Box::new(Self {
			uuid: 0,
		});
    }
}