use std::{
	thread,
	sync::{
		Arc,
		mpsc,
		Mutex,
	},
};

use super::{
	Result,
};

type Job = Box<dyn FnOnce() -> () + Send + 'static>;

pub struct ThreadPool {
	workers: Vec<Worker>,
	sender: Option<mpsc::Sender<Job>>,
}

impl ThreadPool {
	/**
	Create a new [`ThreadPool`].

	# Errors
	If the pool fails to create any worker it will return an error.

	# Panics
	The `new` function will panic if `thread::available_parallelism() - 1` is zero.
	*/
	pub fn new() -> Result<Self> {
		let size = thread::available_parallelism()?.get();
		assert!(size - 1 > 0);
		let (sender, receiver) = mpsc::channel();
		let mut workers = Vec::<Worker>::with_capacity(size);
		let receiver = Arc::new(Mutex::new(receiver));
		for _ in 0..size {
			let worker = Worker::new(Arc::clone(&receiver))?;
			workers.push(worker);
		}
		Ok(ThreadPool {
			workers,
			sender: Some(sender),
		})
	}
	/**
	Creates a job that is then queued for the threads to run.
	The f is a function or closure that will be executed as a job in the thread pool.

	# Panics
	- If you send a job that panics to the thread pool it will cause the entire program
	to panic. This is because the thread panic causes a lock to not be unlocked and causes
	an unrecoverable error.
	*/
	pub fn execute<F>(self: &Self, f: F)
	where
		F: FnOnce() -> () + Send + 'static,
	{
		let job = Box::new(f);
		self.sender.as_ref().expect("ThreadPool destroyed?").send(job).expect("Reciever is gone?");
	}
}

impl Drop for ThreadPool {
	fn drop(self: &mut Self) {
		drop(self.sender.take());
		for worker in &mut self.workers {
			if let Some(thread) = worker.thread.take() {
				thread.join().expect("Thread panicked?");
			}
		}
	}
}

struct Worker {
	thread: Option<thread::JoinHandle<()>>,
}

impl Worker {
	/** 
	Creates a new [`Worker`].

	# Errors
	If the `thread::Builder::new().spawn()` fails it will return an error.
	*/
	fn new(receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Result<Self> {
		let func = move || {
			loop {
				match receiver.lock().unwrap().recv() {
					Ok(job) => job(),
					Err(_) => break,
				}
			}
		};
		Ok(Worker{
			thread: Some(thread::Builder::new().spawn(func)?)
		})
	}
}
