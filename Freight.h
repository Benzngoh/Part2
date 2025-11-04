#pragma once
#include "System.h"
class Cargo;

class Freight :
    public System
{
private:
    std::string letter = "F";
    std::string freighttype;
    int maxcapacity;

public:
    std::string getletter() const override;
    Freight(int idnumber, std::string destination, int timeh, int timem, std::string freighttp); //constructor 
    Freight();
    friend std::ostream& operator<<(std::ostream& out, const Freight& list);
    bool operator==(const Cargo& c) const;
    std::string getfreighttype() const;
    void setmaxcapacity();
    int getcapacity();
    static Freight fromString(const std::string& line);
    static std::string toString(const Freight& f);
};

