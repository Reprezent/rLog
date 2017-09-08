// 
// rlog Library (C++ 11)
//
// Version 0.1 (Last Updated: 8/5/2017)
//
// Description:
//    This class implements a Logging utility for use within
//    any type of program.
//
// Author:
//	  Richard "Alex" Riedel
//


#pragma once

#ifndef RLOG_WRITER_THREAD_SLEEP_TIME

// Defines the total number of milliseconds for the writer thread
// to wait for between flushes. 
#define RLOG_WRITER_THREAD_SLEEP_TIME 1000

#endif


#include <chrono>
#include <fstream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>


class rlog
{
	public:
		rlog();
		rlog(const rlog& logger);
		rlog(rlog&& logger);
		rlog(std::string filename, bool currentTime = false);
		~rlog();

		void log         (std::string message, std::string header = "");
		void debug_log   (std::string message, std::string header = "[DEBUG] ");
		void warning_log (std::string message, std::string header = "[WARNING] ");
		void error_log   (std::string message, std::string header = "[ERROR] ");
		void fatal_log   (std::string message, std::string header = "[FATAL] ");

		void flush();
		bool close();

		std::queue<std::string>::size_type size();

		
	private:

		
		void write(std::string& message);
		void __flush();
		void __run();
		bool __NotEmpty();

		void add(std::string& message);

		void lock();
		void unlock();
	
		bool FLUSH = false;
		const bool print_time;	
		std::string filename;
		std::ofstream out;
		std::queue<std::string> outputQueue;
		std::mutex queue_io_mutex;
		std::unique_lock<std::mutex> queue_out_lock;
		std::thread writer_thread;
		std::condition_variable queueNotEmpty;

};
