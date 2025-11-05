#include "Freight.h"
#include"Cargo.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>

using namespace std;

std::string Freight::getletter() const
{
	return letter;
}


Freight::Freight(int idnumber, string destination, int timeh, int timem, string freighttp) :
	System(idnumber, destination, timeh, timem)
{
    freighttype = freighttp;
    setmaxcapacity();
}

Freight::Freight() {
    freighttype = "MiniMover";
}

bool Freight::operator==(const Cargo& c) const
{
    return (getdest() == c.getdest()) &&
        (gettimeh() == c.gettimeh()) &&
        (gettimem() == c.gettimem());
}

std::string Freight::getfreighttype() const
{
    return freighttype;
}

void Freight::setmaxcapacity()
{
    if(getfreighttype() == "MiniMover") {
        maxcapacity = 2;
    }
    else if (getfreighttype() == "MidiMover") {
        maxcapacity = 5;
    }
    else if (getfreighttype() == "MegaMover") {
        maxcapacity = 12;
	}
    else
		maxcapacity = 0; // Invalid type
}

int Freight::getcapacity()
{
	return maxcapacity;
}

Freight Freight::fromString(const std::string& line)
{
    size_t comma1 = line.find(',');
    size_t comma2 = line.find(',', comma1 + 1);
    size_t comma3 = line.find(',', comma2 + 1);

    if (comma1 == std::string::npos || comma2 == std::string::npos || comma3 == std::string::npos)
        throw std::invalid_argument("Invalid freight line format");

    std::string idStr = line.substr(0, comma1);
    std::string dest = line.substr(comma1 + 1, comma2 - comma1 - 1);
    std::string timeStr = line.substr(comma2 + 1, comma3 - comma2 - comma1 - 1);
    std::string freighttp = line.substr(comma3 + 1);

    if (idStr.size() < 2 || idStr[0] != 'F')
        throw std::invalid_argument("Invalid freight ID prefix");

    int idnum = std::stoi(idStr.substr(1));

	// Find the colon in the time string
	size_t colon = timeStr.find(':');
    if(colon == std::string::npos)
		throw std::invalid_argument("Invalid time format");

	// Extract hour and minute
    int timeh = std::stoi(timeStr.substr(0, colon));
    int timem = std::stoi(timeStr.substr(colon+1, 2));

	std::string ampm = timeStr.substr(timeStr.length() - 2);
	// Convert to 24-hour format
    if (ampm == "PM" && timeh != 12) {
        timeh += 12;
    }
    else if (ampm == "AM" && timeh == 12) {
        timeh = 0;
    }

    return Freight(idnum, dest, timeh, timem, freighttp);
}

std::string Freight::toString(const Freight& f)
{
    std::ostringstream oss;

    // --- 12-hour conversion for output ---
    int h24 = f.gettimeh();
    int m = f.gettimem();
    std::string ampm = (h24 >= 12) ? "pm" : "am";
    int h12 = h24 % 12;
    if (h12 == 0) h12 = 12; // 0 o'clock is 12

    oss << f.getletter() << std::setw(2) << std::setfill('0') << f.getidnum()
        << "," << f.getdest()
        << "," << h12 << ":" << std::setw(2) << std::setfill('0') << m << ampm // New 12h time
        << "," << f.getfreighttype();
    return oss.str();
}

ostream& operator<<(ostream& out, const Freight& list)
{
    // --- 12-hour conversion for display ---
    int h24 = list.gettimeh();
    int m = list.gettimem();
    std::string ampm = (h24 >= 12) ? "pm" : "am";
    int h12 = h24 % 12;
    if (h12 == 0) h12 = 12;
    // ---

    out << list.getletter() << list.getidnum() << " | "
        << list.getdest() << " | "
        << h12 << ":" << setfill('0') << setw(2) << m << ampm // New 12h time
        << " | " << list.getfreighttype() << endl; // Added freight type
    return out;
}
