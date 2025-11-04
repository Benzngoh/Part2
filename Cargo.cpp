#include "Cargo.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include"freight.h"

using namespace std;

std::string Cargo::getletter() const
{
	return letter;
}


Cargo::Cargo(int idnumber, string destination, int timeh, int timem, int cargosz):
	System(idnumber, destination, timeh, timem)
	 {
    cargosize = cargosz;
}

Cargo::Cargo() {
    cargosize = 0;
}

bool Cargo::operator==(const Freight& f) const
{
    return (getdest() == f.getdest()) &&
        (gettimeh() == f.gettimeh()) &&
        (gettimem() == f.gettimem());
}

int Cargo::getcargosize() const
{
    return cargosize;
}

Cargo Cargo::fromString(const std::string& line) {
    size_t comma1 = line.find(',');
    size_t comma2 = line.find(',', comma1 + 1);
    size_t comma3 = line.find(',', comma2 + 1);

    if (comma1 == std::string::npos || comma2 == std::string::npos || comma3 == std::string::npos)
        throw std::invalid_argument("Invalid cargo line format");

	// Extract substrings
    std::string idStr = line.substr(0, comma1);
    std::string dest = line.substr(comma1 + 1 , comma2 - comma1 - 1);
    std::string timeStr = line.substr(comma2 + 1, comma3 - comma2 - comma1 - 1);
    std::string cargoszStr = line.substr(comma3 + 1);

	// Extract ID number and cargo size
    int idnum = std::stoi(idStr.substr(1));
    int cargosz = std::stoi(cargoszStr);

	// Find the colon in the time string
	size_t colon = timeStr.find(':');
    if(colon == std::string::npos)
		throw std::invalid_argument("Invalid time format");

	// Extract hour, minute, and AM/PM
	int timeh = std::stoi(timeStr.substr(0, colon));
	int timem = std::stoi(timeStr.substr(colon + 1 , 2));
	std::string ampm = timeStr.substr(timeStr.length() - 2);

	// Convert to 24-hour format
    if (ampm == "PM" && timeh != 12) {
        timeh += 12;
    } else if (ampm == "AM" && timeh == 12) {
        timeh = 0;
	}

	// Validate cargo ID prefix and size
    if (idStr.size() < 2 || idStr[0] != 'C' || cargosz > 10)
        throw std::invalid_argument("Invalid cargo ID prefix");

	return Cargo(idnum, dest, timeh, timem, cargosz);   // Create and return Cargo object
}

std::string Cargo::toString(const Cargo& c)
{
    std::ostringstream oss;
    oss << c.getletter() << std::setw(2) << std::setfill('0') << c.getidnum()
        << "," << c.getdest()
        << "," << std::setw(4) << std::setfill('0') << c.gettime() << "," << c.getcargosize();
    return oss.str();
}

ostream& operator<<(ostream& out, const Cargo& list)
{
    out << list.getletter() << list.getidnum() << " , "
        << list.getdest() << " , " << setfill('0') << setw(2)
        << list.gettimeh() << ":" << setfill('0') << setw(2) << list.gettimem() << " , " << list.getcargosize() << endl;
    return out;
    // TODO: insert return statement here
}
