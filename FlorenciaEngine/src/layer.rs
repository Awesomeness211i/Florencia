use super::Event;

pub trait Layer {
	fn OnAdd(self: &mut Self);
	fn OnRemove(self: &mut Self);
	fn OnEvent(self: &mut Self, e: &dyn Event);
	fn Render(self: &mut Self);
	fn Update(self: &mut Self, ts: std::time::Duration);
	fn GetUUID(&self) -> u64;

	/** Debug purposes */
	fn GetName(self: &Self) -> &str { return "Unnamed"; }
}

pub struct LayerStack {
	layers: Vec<Box<dyn Layer>>,
	overlayEndIndex: usize,
}

impl Drop for LayerStack {
	fn drop(self: &mut Self) {
		for layer in &mut self.layers {
			layer.OnRemove();
		}
	}
}

impl LayerStack {
	pub fn new() -> Self {
		return Self {
			layers: Vec::new(),
			overlayEndIndex: 0,
		};
	}

	pub fn iter(self: &mut Self) -> &mut Vec<Box<(dyn Layer)>> {
		return &mut self.layers;
	}

	pub fn AddOverlay(self: &mut Self, layer: Box<dyn Layer>) {
		self.layers.insert(0, layer);
		self.layers[0].OnAdd();
		self.overlayEndIndex += 1;
	}

	pub fn RemoveOverlay(&mut self, uuid: u64) {
		if let Some(i) = self.layers[..self.overlayEndIndex].iter().position(|l| { return l.GetUUID() == uuid; }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
			self.overlayEndIndex -= 1;
		}
	}

	pub fn AddLayer(self: &mut Self, layer: Box<dyn Layer>) {
		self.layers.insert(self.overlayEndIndex, layer);
		self.layers[self.overlayEndIndex].OnAdd();
	}

	pub fn RemoveLayer(self: &mut Self, uuid: u64) {
		if let Some(i) = self.layers[self.overlayEndIndex..].iter().position(|l| { return l.GetUUID() == uuid; }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
		}
	}
}
