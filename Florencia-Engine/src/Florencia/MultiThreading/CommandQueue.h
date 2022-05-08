#pragma once
#include <deque>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>

namespace Florencia {

	enum class Command {
		Test = -1,
		Exit, //Shuts down CommandQueue
		Update, //Does Nothing Yet
		Render, //Does Nothing Yet
		OnEvent, //Does Nothing Yet
	};

	//Shuts Down At End Of Application
	class CommandQueue {
	public:
		~CommandQueue();

		void Start();
		void QueueCommand(Command command);

	private:
		void ExecuteCommand(Command command);

		void Run();
		void ShutDown();

		void Test();

		std::thread m_CommandThread;
		std::deque<Command> m_CommandQueue{};
		bool m_Running{ false };
	};

}