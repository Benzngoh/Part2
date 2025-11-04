#include"FreightList.h"
#include"Freight.h"
#include<iostream>
using namespace std;
#include<vector>
#include "ScheduleList.h"

void FreightList::addfreight(const Freight& f)
{
	freights.push_back(f);
}

const vector<Freight>&  FreightList::getFreightList() const  {
	return freights;
}

Freight* FreightList::searchFreight(int idnumber)
{
	for (auto& k : freights) {
		if (k.getidnum() == idnumber) {
			return &k;
		}
	}
	// If we finish the loop without finding it
	return nullptr;
}

bool FreightList::editFreight(int idnumber, const Freight& newData) {
    Freight* found = searchFreight(idnumber);
    if (!found) {
        return false;  // Not found
    }

    // Validate time
    if (!isValidTime(newData.gettimeh(), newData.gettimem())) {
        return false;
    }

    // Update fields
    found->setidnum(newData.getidnum());
    found->setdest(newData.getdest());
    found->settime(newData.gettimeh(), newData.gettimem());

    return true;
}

bool FreightList::removeFreight(int idnumber) {
    Freight* found = searchFreight(idnumber);
    if (found != nullptr) {
        auto index = found - &freights[0];
        freights.erase(freights.begin() + index);
        return true;
    }
    return false;
}

// newly added function
bool FreightList::isValidTime(int hour, int minute) {
	return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

std::vector<Freight> FreightList::getUnmatchedFreight() const
{
    return unmatchedFreight;
}

void FreightList::addunmatched(const Freight f)
{
    for (const Freight& existing : unmatchedFreight) {    //loops to check every cargo in the unmatchedcargo vector
        if (existing.getidnum() == f.getidnum()) {
            return;
        }
    }
    unmatchedFreight.push_back(f);
}


void FreightList::removeunmatched(const Freight& f) {
    for (auto it = unmatchedFreight.begin(); it != unmatchedFreight.end(); ++it) {//removing based on idnumber
        if (it->getidnum() == f.getidnum()) {
            unmatchedFreight.erase(it);
            return;
        }
    }
}

void FreightList::clearunmatched() { //clears entire list of unmatched freight
    unmatchedFreight.clear(); 
}

void FreightList::identifyUnmatched(const ScheduleList& slist)
{
    clearunmatched();
    
    for (const Freight& f : freights) {
        bool scheduled = false;

        for (const Schedule& s : slist.getSchedule()) {
            const Freight* sf = s.getfreightsch();

            if (sf &&
                sf->getidnum() == f.getidnum() &&
                sf->getdest() == f.getdest() &&
                sf->gettime() == f.gettime()) {
                scheduled = true;
                break;
            }
        }
        if (!scheduled) {
            addunmatched(f);
        }
    }
}

