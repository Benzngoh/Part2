#pragma once
#include<iostream>
#include "System.h"
class Freight;

class Cargo :
    public System
{
private:
    std::string letter = "C";
    int cargosize;

public:
    std::string getletter() const override;
    Cargo( int idnumber, std::string destination, int timeh, int timem, int cargosz); //constructor 
    Cargo(); //default constructor/
    friend std::ostream& operator<<(std::ostream& out, const Cargo& list);
    bool operator==(const Freight& f) const;
    int getcargosize() const;

    //serialise
    static Cargo fromString(const std::string& line);
    static std::string toString(const Cargo& c);
};

