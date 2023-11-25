use super::Event;

pub trait Layer {
	fn OnAdd(&mut self);
	fn OnRemove(&mut self);
	fn OnEvent(&mut self, e: &dyn Event);
	fn Render(&mut self);
	fn Update(&mut self, ts: std::time::Duration);
	fn GetUUID(&self) -> u64;

	/** Debug purposes */
	fn GetName(&self) -> &str { "Unnamed" }
}

#[derive(Default)]
pub struct LayerStack {
	layers: Vec<Box<dyn Layer>>,
	overlayEndIndex: usize,
}

impl Drop for LayerStack {
	fn drop(&mut self) {
		for layer in &mut self.layers {
			layer.OnRemove();
		}
	}
}

impl LayerStack {
	pub fn iter(&mut self) -> &mut Vec<Box<(dyn Layer)>> {
		&mut self.layers
	}

	pub fn AddOverlay(&mut self, layer: Box<dyn Layer>) {
		self.layers.insert(0, layer);
		self.layers[0].OnAdd();
		self.overlayEndIndex += 1;
	}

	pub fn RemoveOverlay(&mut self, uuid: u64) {
		if let Some(i) = self.layers[..self.overlayEndIndex].iter().position(|l| { l.GetUUID() == uuid }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
			self.overlayEndIndex -= 1;
		}
	}

	pub fn AddLayer(&mut self, layer: Box<dyn Layer>) {
		self.layers.insert(self.overlayEndIndex, layer);
		self.layers[self.overlayEndIndex].OnAdd();
	}

	pub fn RemoveLayer(&mut self, uuid: u64) {
		if let Some(i) = self.layers[self.overlayEndIndex..].iter().position(|l| { l.GetUUID() == uuid }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
		}
	}
}
