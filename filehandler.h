#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include"CargoList.h"
#include"FreightList.h"
#include"ScheduleList.h"
class filehandler
{
public:
	//read from lines to vectors
	static bool readLines(const std::string& filename, std::vector<std::string > & lines);
	
	//write from lines to vectors
	static bool writeLines(const std::string& filename, const std::vector<std::string > & lines);

	//clear contents
	static bool clearFile(const std::string& filename);
};

