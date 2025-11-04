#pragma once
#include<vector>
#include<iostream>
#include "Cargo.h"

class ScheduleList;
class Freight;

class CargoList 
{
private:
    std::vector<Cargo> cargos; //setting cargos as a vector in the format of Cargo constructor(int, string, int, int),allows the vector to use public function in the cargo class
    std::vector<Cargo> unmatchedCargo;  //vector to hold unmatched cargos
public:
    void addcargo(const Cargo c); //add the cargo input into the cargos vector
    const std::vector<Cargo>& getCargoList() const ; //function to allow to call cargos vector from outside the class like from in main
    Cargo* searchcargo( int idnumber);  

    bool editCargo(int idnumber, const Cargo& newData);
    bool removeCargo(int idnumber);
    bool isValidTime(int hour, int minute);

    const std::vector<Cargo> getUnmatchedCargo() const;
    void addunmatched(const Cargo c);  //function to add cargos into unmatched vector
    void removeunmatched(const Cargo& c);
    void clearunmatched();
    void identifyUnmatched(const ScheduleList& slist);
};

