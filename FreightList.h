#pragma once
#include<vector>
#include<iostream>
#include<ostream>
#include "Freight.h"

class ScheduleList;
class FreightList
{
    private:
        std::vector<Freight> freights; //setting cargos as a vector in the format of Cargo constructor(int, string, int, int),allows the vector to use public function in the cargo class
        std::vector<Freight> unmatchedFreight;
    public:
        void addfreight(const Freight& f); //add the cargo input into the cargos vector
        const std::vector<Freight>& getFreightList() const; //function to allow to call cargos vector from outside the class like from in main
        Freight* searchFreight(int idnumber);
        bool editFreight(int idnumber, const Freight& newData);
        bool removeFreight(int idnumber);
		bool isValidTime(int hour, int minute);
        std::vector<Freight> getUnmatchedFreight() const;
        void addunmatched(const Freight f);
        void removeunmatched(const Freight& f);
        void clearunmatched();
        void identifyUnmatched(const ScheduleList& slist);

        
    };

