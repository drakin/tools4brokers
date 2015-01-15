// Kobyshev S(tools4brokers).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <boost\thread.hpp>
#include <boost\filesystem.hpp>

static int sum = 0;

void file_check(std::string path){
	std::ostringstream buffer;
	try{
		int tmp = 0;
		std::ifstream input_file(path);
		input_file>>tmp;
		input_file.close();
		sum += tmp;
		buffer<<path.substr(path.find_last_of("\\")+1)<<": "<<tmp<<std::endl;
	}catch(std::exception e){
		buffer<<"Error with "<<path<<std::endl;
	}
	std::cout<<buffer.str();
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc == 1){
		std::cout<<"Error! Enter file paths as parameters."<<std::endl;
		return 1;
	}
	boost::thread_group all_threads; // or we can use std::list<boost::thread> all_threads;
	boost::filesystem::directory_iterator end;
	for(int i=1; i<argc; i++)
	{
		for(boost::filesystem::directory_iterator i(argv[i]);i != end; i++)
			if (boost::filesystem::is_regular_file(i->path()))
			{
				all_threads.add_thread(new boost::thread(file_check,i->path().string()));
			}
			
	}
	all_threads.join_all();
	std::cout<<"Total sum: "<<sum<<std::endl;
	return 0;
}

