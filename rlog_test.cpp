#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "rlog.hpp"


#define NUM_THREADS 10
rlog logger;

void addstuff(std::string name)
{
	for(unsigned int i = 0; i < 1000; i++)
	{
		logger.log(name + " Hello!!!!" + " " + std::to_string(i));
		logger.debug_log(name + " Thing " + std::to_string(i));
		logger.warning_log(name + " Uhhhhhhhhhhhhh " + std::to_string(i));
		logger.error_log(name + " Buffer overflowwwwwwwwwwwwwww " + std::to_string(i));
		logger.fatal_log(name + " RIP program" + std::to_string(i));
	}
}



int main(int argc, char** argv)
{
//	std::cout << "SIZE OF rLOG " << sizeof(rlog) << std::endl;
	std::vector<std::thread> threads;
	for(unsigned int i = 0; i < NUM_THREADS; i++)
	{
		threads.push_back(std::thread(addstuff, std::to_string(i)));
	}

	for(unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}	
}

