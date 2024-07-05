use super::Result;

pub struct WindowData {
	pub vsync: bool,
	pub polling: bool,

	pub title: String,
	pub dimensions: (u32, u32),
}

pub struct Window {
}

impl Window {
	pub fn new(_data: WindowData) -> Result<Self> {
		Ok(Window {})
	}

	pub fn GetSize(&self) -> (u32, u32) { (0, 0) }
	
	pub fn Update(&mut self) {
	}
}
