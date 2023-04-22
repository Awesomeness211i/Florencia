use super::Event;

pub trait Layer {
	fn OnAdd(self: &Self);
	fn OnRemove(self: &Self);
	fn OnEvent(self: &Self, e: &dyn Event);
	fn Render(self: &Self);
	fn Update(self: &Self, ts: f64);
	fn GetUUID(&self) -> u64;

	//Debug purposes
	fn GetName(self: &Self) -> &str { return "Unnamed"; }
}

pub struct LayerStack {
	layers: Vec<Box<dyn Layer>>,
	layerInsertIndex: usize,
	overlayInsertIndex: usize,
}

impl Drop for LayerStack {
	fn drop(self: &mut Self) {
		for layer in &self.layers {
			layer.OnRemove();
		}
	}
}

impl LayerStack {
	pub fn new() -> Self {
		return Self {
			layers: Vec::new(),
			layerInsertIndex: 0,
			overlayInsertIndex: 0,
		};
	}
	pub fn iter(&self) -> impl Iterator<Item = &Box<dyn Layer>> {
		return self.layers.iter().rev();
	}

	pub fn AddOverlay(&mut self, layer: Box<dyn Layer>) {
		layer.OnAdd();
		self.layers.push(layer);
		self.overlayInsertIndex += 1;
	}
	pub fn RemoveOverlay(&mut self, uuid: u64) {
		if let Some(i) = self.layers[self.layerInsertIndex..self.overlayInsertIndex].iter().position(|l| { return l.GetUUID() == uuid; }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
			self.overlayInsertIndex -= 1;
		}
	}
	pub fn AddLayer(self: &mut Self, layer: Box<dyn Layer>) {
		layer.OnAdd();
		self.layers.insert(self.layerInsertIndex, layer);
		self.layerInsertIndex += 1;
	}
	pub fn RemoveLayer(self: &mut Self, uuid: u64) {
		if let Some(i) = self.layers[..self.layerInsertIndex].iter().position(|l| { return l.GetUUID() == uuid; }) {
			self.layers[i].OnRemove();
			self.layers.remove(i);
			self.layerInsertIndex -= 1;
		}
	}
}