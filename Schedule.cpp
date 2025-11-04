#include "Schedule.h"
#include<iomanip>
#include<sstream>
using namespace std;

const Cargo* Schedule::getcargosch() const
{
	return cargosch;
}

const Freight* Schedule::getfreightsch() const
{
		return freightsch;
}


bool Schedule::match() const
{
	return *cargosch == *freightsch; //useing ==operator to return whether time and dest of cargo and freight match or not(bool)
		
}

Schedule::Schedule(int sid,const Freight& f ,const Cargo& c):
	schid(sid), cargosch(&c), freightsch(&f)
{
}

Schedule::Schedule(): 
	schid(0),cargosch(nullptr) ,freightsch(nullptr)
{}

int Schedule::getid() const
{
	return schid;
}

static Schedule fromString(const std::string& line) {
    size_t comma1 = line.find(',');
    size_t comma2 = line.find(',', comma1 + 1);
    size_t comma3 = line.find(',', comma2 + 1);
    size_t comma4 = line.find(',', comma3 + 1);
    size_t comma5 = line.find(',', comma4 + 1);
    size_t comma6 = line.find(',', comma5 + 1);

    if (comma1 == std::string::npos || comma2 == std::string::npos || comma3 == std::string::npos ||
        comma4 == std::string::npos || comma5 == std::string::npos || comma6 == std::string::npos) {
        throw std::invalid_argument("Invalid schedule line format");
    }

    // Parse cargo info
    std::string cargoIdStr = line.substr(0, comma1);
    std::string cargoDest = line.substr(comma1 + 1, comma2 - comma1 - 1);
    std::string cargoTimeStr = line.substr(comma2 + 1, comma3 - comma2 - 1);

    int cargoId = std::stoi(cargoIdStr.substr(1)); // assuming format like C02
    int cargoTimeH = std::stoi(cargoTimeStr.substr(0, 2));
    int cargoTimeM = std::stoi(cargoTimeStr.substr(2, 2));

    // Parse freight info
    std::string freightIdStr = line.substr(comma3 + 1, comma4 - comma3 - 1);
    std::string freightDest = line.substr(comma4 + 1, comma5 - comma4 - 1);
    std::string freightTimeStr = line.substr(comma5 + 1, comma6 - comma5 - 1);

    int freightId = std::stoi(freightIdStr.substr(1));
    int freightTimeH = std::stoi(freightTimeStr.substr(0, 2));
    int freightTimeM = std::stoi(freightTimeStr.substr(2, 2));

    // Create Cargo and Freight objects (assuming public constructors)
    Cargo c(cargoId, cargoDest, cargoTimeH, cargoTimeM);
    Freight f(freightId, freightDest, freightTimeH, freightTimeM);

    // Create Schedule with ID, cargo, freight
    return Schedule(cargoId, f, c);
}

std::string Schedule::toString(const Schedule& s)
{
    const Cargo* c = s.getcargosch();
    const Freight* f = s.getfreightsch();

    if (!c || !f) return "Incomplete Schedule";

    std::ostringstream oss;
    oss << s.getid() << ","
        << c->getletter() << c->getidnum() << "," << c->getdest() << ","
        << std::setw(2) << std::setfill('0') << c->gettimeh()
        << std::setw(2) << std::setfill('0') << c->gettimem() << ","
        << f->getletter() << f->getidnum() << "," << f->getdest() << ","
        << std::setw(2) << std::setfill('0') << f->gettimeh()
        << std::setw(2) << std::setfill('0') << f->gettimem();
    return oss.str();
}

ostream& operator<<(ostream& out, const Schedule& list)
{
	const Cargo* c = list.getcargosch();
	const Freight* f = list.getfreightsch();

	if (!c || !f) {
		out << "Schedule " << list.getid() << "is incomplete.\n";
	}
	out << "Schedule " << list.getid() << " => "
		<< c->getletter() << c->getidnum() << " & "
		<< f->getletter() << f->getidnum() << " | "
		<< c->getdest() << " | " << setfill('0') << setw(2)
		<< c->gettimeh() << ":" << setfill('0') << setw(2) << c->gettimem() << "\n";
	return out;
}


