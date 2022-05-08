#include "CommandQueue.h"

namespace Florencia {

	CommandQueue::~CommandQueue() { ShutDown(); }

	void CommandQueue::Start() {
		if(m_CommandThread.joinable()) {
			return;
		}

		m_CommandQueue.clear();
		m_CommandThread = std::thread(&CommandQueue::Run, this);
	}

	void CommandQueue::QueueCommand(Command command) {
		if(!m_Running) {
			return;
		}
		m_CommandQueue.push_back(command);
	}

	void CommandQueue::ExecuteCommand(Command command) {
		switch(command) {
			case Command::Exit: ShutDown(); return;
			case Command::Test: Test(); return;
		}
	}

	void CommandQueue::Run() {
		m_Running = true;
		while(m_Running) {
			if(m_CommandQueue.size() == 0) { continue; }

			ExecuteCommand(m_CommandQueue.front());
			m_CommandQueue.pop_front();
		}
	}

	void CommandQueue::ShutDown() {
		if(m_CommandThread.joinable()) {
			m_Running = false;
			m_CommandThread.detach();
		}
	}

	void CommandQueue::Test() {
		std::cout << "This is a Test\n";
	}

}