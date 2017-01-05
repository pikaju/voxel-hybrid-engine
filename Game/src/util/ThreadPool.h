#pragma once

namespace std {
	class thread;
}

namespace util {

	class ThreadTask
	{
	public:
		ThreadTask() : m_valid(false), m_function(nullptr), m_parameter(nullptr) {  }
		ThreadTask(void(*function)(void*), void* parameter) : m_valid(true), m_function(function), m_parameter(parameter) {  }
		~ThreadTask() {  }

		void execute()
		{
			m_function(m_parameter);
			m_valid = false;
		}

		inline bool isValid() const { return m_valid; }
	private:
		bool m_valid;
		void(*m_function)(void*);
		void* m_parameter;
	};

	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();

		void start(unsigned int numWorkers);
		void stop();

		void addTask(const ThreadTask& task);

		inline bool isSaturated() const { return m_numIdleWorkers == 0; }
		inline bool isRunning() const { return m_running; }
	protected:
		static void workerThread(ThreadPool* threadPool, unsigned int index);
	private:
		std::thread** m_workers;
		unsigned int m_numWorkers;
		ThreadTask* m_tasks;
		unsigned int m_numIdleWorkers;
		bool m_running;
	};

}