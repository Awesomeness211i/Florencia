use FlorenciaEngine::*;

pub struct EditorLayer {

}

impl Layer for EditorLayer {
	fn OnAdd(self: &Self) {
		
	}
	fn OnRemove(self: &Self) {
		
	}
	fn OnEvent(self: &Self, e: &dyn Event) {
		
	}
	fn Update(self: &Self, ts: std::time::Duration) {
		
	}
	fn Render(self: &Self) {
		
	}
	fn GetUUID(self: &Self) -> u64 {
		0
	}
}

impl EditorLayer {
	pub fn new() -> Box<Self> {
        return Box::new(Self {
			
		});
    }
}