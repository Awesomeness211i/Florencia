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
	fn OnEvent(self: &mut Self, _e: &dyn Event) {
		
	}
	fn Update(self: &Self, _ts: std::time::Duration) {

	}
	fn Render(self: &Self) {
		
	}
}

impl EditorLayer {
	pub fn new() -> Box<Self> {
        return Box::new(Self {
		});
    }
}