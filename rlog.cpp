// 
// rlog Library (C++ 11)
//
// Version 0.1 (Last Updated: 5/10/2017)
//
// Description:
//    This class implements a Logging utility for use within
//    any type of program.
//
// Author:
//	  Richard "Alex" Riedel
//


#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <queue>
#include <string>
#include <thread>
#include <utility>

#include "rlog.hpp"

rlog::rlog() : print_time(true), writer_thread(&rlog::__run, this)
{
	writer_thread.detach();

	const time_t temp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string tempStr = std::string("Log ") + ctime(&temp);
	tempStr.pop_back();
	tempStr.append(".txt");
	std::replace(tempStr.begin(), tempStr.end(), ' ', '_');
	filename = tempStr;
	out.open(filename, std::ofstream::out | std::ofstream::app);

}
rlog::rlog(std::string filename, bool currentTime) : print_time(currentTime), writer_thread(&rlog::__run, this)
{
	writer_thread.detach();
	this->filename = filename;
	out.open(filename, std::ofstream::out | std::ofstream::app);
}

rlog::rlog(const rlog& logger) : print_time(logger.print_time),
								 outputQueue(std::move(logger.outputQueue))
{
	filename = logger.filename;
	FLUSH = logger.FLUSH;
	out.open(filename, std::ofstream::out | std::ofstream::app);
}

rlog::~rlog()
{
	__flush();
	out.close();
}

void rlog::log(std::string message, std::string header)
{
	add(header.append(message));
}

void rlog::debug_log(std::string message, std::string header)
{
	add(header.append(message));
}

void rlog::warning_log(std::string message, std::string header)
{
	add(header.append(message));
}

void rlog::error_log(std::string message, std::string header)
{
	add(header.append(message));
}

void rlog::fatal_log(std::string message, std::string header)
{
	add(header.append(message));
}

void rlog::flush()
{
	FLUSH = true;
}

std::queue<std::string>::size_type rlog::size()
{
	return outputQueue.size();
}


void rlog::write(std::string& message)
{
	out << message << std::endl;
}

void rlog::add(std::string& message)
{
	lock();

	outputQueue.push(message);

	unlock();
}

void rlog::lock()
{
	queue_io_mutex.lock();
}

void rlog::unlock()
{
	queue_io_mutex.unlock();
}

void rlog::__flush()
{
	lock();
	while(!outputQueue.empty())
	{
		write(outputQueue.front());
		outputQueue.pop();
	}
	unlock();
}

void rlog::__run()
{
	while(true)
	{
		if(FLUSH)
		{
			__flush();
			FLUSH = false;
		}
		/*queueNotEmpty.wait(queue_out_lock, [this]() -> bool
													{
														bool ret;
														lock();
														ret = !outputQueue.empty();
														unlock();
														return ret;
													});
	*/

			lock();
			if(!outputQueue.empty())
			{
				write(outputQueue.front());
				outputQueue.pop();
			}
			unlock();
		
	}
}
