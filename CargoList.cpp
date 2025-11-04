#include "CargoList.h"
#include "Cargo.h"
#include<iostream>
using namespace std;
#include<vector>
#include "ScheduleList.h"

void CargoList::addcargo(const Cargo c)
{
	cargos.push_back(c);
}
const std::vector<Cargo>&  CargoList::getCargoList() const  {
	return cargos;
}

Cargo* CargoList::searchcargo( int idnumber)
{
	for (auto& k : cargos) {
		if (k.getidnum() == idnumber) {
			return &k;
		}
	}
	// If we finish the loop without finding it
	return nullptr;
}

bool CargoList::editCargo(int idnumber, const Cargo& newData) {
    Cargo* found = searchcargo(idnumber);
    if (!found) {
        return false;  // Not found
    }

    // Validate time before updating
    if (!isValidTime(newData.gettimeh(), newData.gettimem())) {
        return false;  // Invalid time
    }

    // Update found cargo fields
    found->setidnum(newData.getidnum());
    found->setdest(newData.getdest());
    found->settime(newData.gettimeh(), newData.gettimem());

    return true;
}

bool CargoList::removeCargo(int idnumber) {
    Cargo* found = searchcargo(idnumber);
    if (found != nullptr) {
        auto index = found - &cargos[0];
        cargos.erase(cargos.begin() + index);
        return true;
    }
    return false;
}

// newly added functions
bool CargoList::isValidTime(int hour, int minute) {
	return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

const std::vector<Cargo> CargoList::getUnmatchedCargo() const
{
    return unmatchedCargo;
}

void CargoList::addunmatched(const Cargo c)
{
    for(const Cargo& existing : unmatchedCargo){    //loops to check every cargo in the unmatchedcargo vector
        if (existing.getidnum() == c.getidnum()) {
            return;
        }
    }
    unmatchedCargo.push_back(c);
}


void CargoList::removeunmatched(const Cargo& c) {
    for (auto it = unmatchedCargo.begin(); it != unmatchedCargo.end(); ++it) {//removing based on idnumber
        if (it->getidnum() == c.getidnum()) {
            unmatchedCargo.erase(it);
            return;
        }
    }
}

void CargoList::clearunmatched() { //clears entire list of unmatched cargo
    unmatchedCargo.clear(); 
}

void CargoList::identifyUnmatched(const ScheduleList& slist)
{
    clearunmatched();

    for (const Cargo& c : cargos)
    {
        bool scheduled = false;

        for (const Schedule& s : slist.getSchedule()) {
            const Cargo* sc = s.getcargosch();

            if (sc &&
                sc->getidnum() == c.getidnum() &&
                sc->getdest() == c.getdest() &&
                sc->gettime() == c.gettime()) {
                scheduled = true;
                break;
            }
        }

        if (!scheduled) {
            addunmatched(c);
        }
    }
}






