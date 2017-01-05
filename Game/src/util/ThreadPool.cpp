#include "ThreadPool.h"

#include <thread>

#include "../debug/Debug.h"

namespace util {

	ThreadPool::ThreadPool() : m_workers(nullptr), m_numWorkers(0), m_tasks(nullptr), m_running(false)
	{
	}
	
	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::start(unsigned int numWorkers)
	{
		stop();
		m_numWorkers = numWorkers;
		m_workers = new std::thread*[m_numWorkers];
		m_running = true;
		m_tasks = new ThreadTask[m_numWorkers];
		m_numIdleWorkers = m_numWorkers;
		for (unsigned int i = 0; i < m_numWorkers; i++) {
			m_workers[i] = new std::thread(workerThread, this, i);
		}
	}

	void ThreadPool::stop()
	{
		if (m_workers != nullptr) {
			m_running = false;
			for (unsigned int i = 0; i < m_numWorkers; i++) {
				m_workers[i]->join();
				delete m_workers[i];
			}
			delete[] m_workers;
			m_workers = nullptr;
			m_running = false;
		}
		if (m_tasks != nullptr) {
			delete[] m_tasks;
			m_tasks = nullptr;
		}
	}

	void ThreadPool::addTask(const ThreadTask& task)
	{
		if (isSaturated()) {
			const_cast<ThreadTask&>(task).execute();
		}
		else {
			m_numIdleWorkers--;
			for (unsigned int i = 0; i < m_numWorkers; i++) {
				if (!m_tasks[i].isValid()) {
					m_tasks[i] = task;
					return;
				}
			}
		}
	}

	void ThreadPool::workerThread(ThreadPool* threadPool, unsigned int index)
	{
		while (threadPool->isRunning()) {
			if (threadPool->m_tasks[index].isValid()) {
				threadPool->m_tasks[index].execute();
				threadPool->m_numIdleWorkers++;
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
		}
	}

}