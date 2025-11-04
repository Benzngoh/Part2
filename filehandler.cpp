#include "filehandler.h"
#include<fstream>

bool filehandler::readLines(const std::string& filename, std::vector<std::string>& lines)
{
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	return true;
}

bool filehandler::writeLines(const std::string& filename, const std::vector<std::string>& lines)
{
	std::ofstream file(filename);
	if (!file.is_open()) return false;

	for (const auto& line : lines) {
		file << line << "\n";
	}
	return true;
}

bool filehandler::clearFile(const std::string& filename)
{
	std::ofstream file(filename, std::ios::trunc);
	return file.is_open();
}


