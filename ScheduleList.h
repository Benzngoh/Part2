#pragma once
#include "Schedule.h"
#include <vector>
#include "CargoList.h"
#include"FreightList.h"

class ScheduleList
{
private: 
    std::vector<Schedule> schedulelist;
    int currentid = 1;
public:
    void addmatched(const Freight& f,const Cargo& c);
    const std::vector<Schedule>& getSchedule() const ;
    bool removeSchedule(int idnumber);
    void setCurrentId(int id);
    void clearSchedules();
    void generateSchedules(CargoList& clist, FreightList& flist);
    void updateScheduleandUnmatched(CargoList& clist, FreightList& flist);
};

