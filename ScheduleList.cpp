#include "ScheduleList.h"
#include"Schedule.h"
#include<vector>
using namespace std;

void ScheduleList::addmatched(const Freight& f ,const Cargo& c)
{
	Schedule s(currentid, f, c); //give current id (c and f are alr passed as reference)
	if (s.match()) {			//then call match() to see if match
		schedulelist.push_back(s);	//pushback if match
		currentid++;			//add 1 to id for the next comparison
	}
}

const std::vector<Schedule>& ScheduleList::getSchedule() const
{
	return schedulelist;
}

bool ScheduleList::removeSchedule(int idnumber)
{
    for (auto it = schedulelist.begin(); it != schedulelist.end(); ++it) {
        if (it->getid() == idnumber) {
            schedulelist.erase(it);
            return true;
        }
    }
    return false;  // Not found
}

void ScheduleList::setCurrentId(int id)
{
	currentid = id;
}

// newly added function to clear all schedules
void ScheduleList::clearSchedules()
{
	schedulelist.clear();
}

void ScheduleList::generateSchedules(CargoList& clist, FreightList& flist)
{
    for (const Freight& f : flist.getFreightList()) {
        for (const Cargo& c : clist.getCargoList()) {
            if (c == f) {
                // Call ScheduleList's own method
                addmatched(f, c);
                break;
            }
           }
          }
    }

void ScheduleList::updateScheduleandUnmatched(CargoList& clist, FreightList& flist)
{
    clearSchedules();
    setCurrentId(1);
    generateSchedules(clist, flist);

    clist.identifyUnmatched(*this);
    flist.identifyUnmatched(*this);
}







