#ifndef __STATUS_BAR_HPP__
#define __STATUS_BAR_HPP__

#include "item.hpp"

#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>

class StatusBar
{
public:
	StatusBar();
	~StatusBar();

	void Start();

	void SetValue();

	void SetRoot();

	std::string GetFifoFile();

	std::vector<std::string> GetItemNames();

private:
	std::vector<Item*> items_;	
	std::vector<std::thread> event_threads_;

	std::string status_bar_str_;

	std::mutex root_mutex_;

	void CreateFifoThread();
	void ReadFifo();

	void CreateItems();

	std::thread read_fifo_thread_;

	std::atomic_bool is_running_;
};


#endif // __STATUS_BAR_HPP__